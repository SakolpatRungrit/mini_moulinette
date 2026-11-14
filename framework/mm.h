/* ************************************************************************** */
/*                                                                            */
/*   mm.h - tiny test framework for mini-moulinette                           */
/*                                                                            */
/*   Every CASE runs in its own forked process, so a segfault, an infinite    */
/*   loop or a memory error only fails that one case.                         */
/*                                                                            */
/*   CASE("desc", ...)  { ... }   a required check (counts toward OK/KO)      */
/*   SOFT("desc", ...)  { ... }   an extra edge case: failing it only warns   */
/*                                                                            */
/*   Inside a case:                                                           */
/*     CHECK_INT(label, got, expected)                                        */
/*     CHECK_STR(label, got, expected)       (NULL-safe)                      */
/*     CHECK_MEM(label, got, expected, n)                                     */
/*     CHECK_PTR(label, got, expected, base) (shows base+offset)              */
/*     CHECK_SIGN(label, got, expected)      (only the sign must match)       */
/*     CHECK_OUTPUT(expected) / CHECK_OUTPUT_N(expected, n)  (stdout)         */
/*     CHECK(cond, fmt, ...)                                                  */
/*     RUN(argv0, args...)  run the student's program (C06), then             */
/*     CHECK_PROG_OUTPUT(expected)                                            */
/*                                                                            */
/* ************************************************************************** */

#ifndef MM_H
# define MM_H

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <stdarg.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/types.h>
# include <sys/wait.h>

# define MM_U __attribute__((unused))
# define MM_ASAN_EXIT 86
# define MM_EXIT_PASS 70
# define MM_EXIT_FAIL 71

static int		mm_pass MM_U;
static int		mm_total MM_U;
static int		mm_warn MM_U;
static int		mm_failed MM_U;
static int		mm_msg_fd MM_U = -1;
static int		mm_out_checked MM_U;
static int		mm_timeout_next MM_U;
static char		mm_desc[2048] MM_U;
static int		mm_shown MM_U;
static int		mm_shown_warn MM_U;
static int		mm_hidden_fail MM_U;
static int		mm_hidden_warn MM_U;
static char		*mm_prog_out MM_U;
static size_t	mm_prog_len MM_U;

/* ------------------------------------------------------------------------ */
/* small utils                                                              */
/* ------------------------------------------------------------------------ */

MM_U static int	mm_env_int(const char *name, int def)
{
	const char	*v = getenv(name);

	if (!v || !*v)
		return (def);
	return (atoi(v));
}

MM_U static const char	*mm_col(const char *code)
{
	return (mm_env_int("MM_COLOR", 0) ? code : "");
}

# define MM_GREEN mm_col("\033[32m")
# define MM_RED mm_col("\033[31m")
# define MM_YELLOW mm_col("\033[33m")
# define MM_GREY mm_col("\033[90m")
# define MM_BOLD mm_col("\033[1m")
# define MM_RESET mm_col("\033[0m")

MM_U static int	mm_tmpfd(void)
{
	char	path[] = "/tmp/mini-moul.XXXXXX";
	int		fd;

	fd = mkstemp(path);
	if (fd < 0)
	{
		perror("mini-moulinette: mkstemp");
		exit(2);
	}
	unlink(path);
	return (fd);
}

MM_U static char	*mm_read_fd(int fd, size_t *len)
{
	off_t	size = lseek(fd, 0, SEEK_END);
	char	*buf;
	ssize_t	r;

	if (size < 0)
		size = 0;
	buf = malloc((size_t)size + 1);
	r = size > 0 ? pread(fd, buf, (size_t)size, 0) : 0;
	if (r < 0)
		r = 0;
	buf[r] = '\0';
	if (len)
		*len = (size_t)r;
	return (buf);
}

/* Escape bytes for display: "a\nb\x01". Rotating buffers so several calls
   can be used in one printf. Long data is cut around `center`. */
MM_U static const char	*mm_show_at(const void *ptr, size_t n, size_t center)
{
	static char		bufs[8][1024];
	static int		slot;
	char			*out;
	const unsigned char	*s = ptr;
	size_t			start = 0;
	size_t			end = n;
	size_t			i;
	int				k = 0;

	out = bufs[slot++ % 8];
	if (!ptr)
		return ("NULL");
	if (n > 90)
	{
		start = center > 30 ? center - 30 : 0;
		end = start + 70 < n ? start + 70 : n;
	}
	if (start > 0)
		k += sprintf(out + k, "...");
	out[k++] = '"';
	for (i = start; i < end && k < 1000; i++)
	{
		if (s[i] == '\n')
			k += sprintf(out + k, "\\n");
		else if (s[i] == '\t')
			k += sprintf(out + k, "\\t");
		else if (s[i] == '\0')
			k += sprintf(out + k, "\\0");
		else if (s[i] == '"' || s[i] == '\\')
			k += sprintf(out + k, "\\%c", s[i]);
		else if (s[i] < 32 || s[i] > 126)
			k += sprintf(out + k, "\\x%02x", s[i]);
		else
			out[k++] = (char)s[i];
	}
	out[k++] = '"';
	out[k] = '\0';
	if (end < n)
		k += sprintf(out + k, "... (%zu bytes)", n);
	return (out);
}

MM_U static const char	*mm_showm(const void *p, size_t n)
{
	return (mm_show_at(p, n, 0));
}

MM_U static const char	*mm_show(const char *s)
{
	return (mm_show_at(s, s ? strlen(s) : 0, 0));
}

/* ------------------------------------------------------------------------ */
/* reporting (child side)                                                   */
/* ------------------------------------------------------------------------ */

MM_U static void	mm_fail(const char *fmt, ...)
{
	va_list	ap;

	va_start(ap, fmt);
	vdprintf(mm_msg_fd, fmt, ap);
	va_end(ap);
	dprintf(mm_msg_fd, "\n");
	mm_failed = 1;
}

MM_U static void	mm_diff(const char *label, const void *got, size_t gn,
		const void *exp, size_t en)
{
	size_t	d = 0;
	size_t	line = 1;
	size_t	i;

	while (d < gn && d < en && ((const char *)got)[d] == ((const char *)exp)[d])
		d++;
	for (i = 0; i < d; i++)
		if (((const char *)exp)[i] == '\n')
			line++;
	mm_fail("%s:\n  expected: %s\n  got:      %s", label,
		mm_show_at(exp, en, d), mm_show_at(got, gn, d));
	if (line > 1 || memchr(exp, '\n', en))
		mm_fail("  (first difference at byte %zu, line %zu)", d, line);
	else if (en > 20 || gn > 20)
		mm_fail("  (first difference at byte %zu)", d);
}

# define CHECK(cond, ...) do { if (!(cond)) mm_fail(__VA_ARGS__); } while (0)

# define CHECK_INT(label, got, exp) do { \
	long long mm_g_ = (long long)(got); long long mm_e_ = (long long)(exp); \
	if (mm_g_ != mm_e_) \
		mm_fail("%s: expected %lld, got %lld", label, mm_e_, mm_g_); \
} while (0)

# define CHECK_SIGN(label, got, exp) do { \
	long long mm_g_ = (long long)(got); long long mm_e_ = (long long)(exp); \
	int mm_gs_ = (mm_g_ > 0) - (mm_g_ < 0); int mm_es_ = (mm_e_ > 0) - (mm_e_ < 0); \
	if (mm_gs_ != mm_es_) \
		mm_fail("%s: expected %s, got %lld", label, mm_es_ == 0 ? "0" \
			: (mm_es_ < 0 ? "a negative number" : "a positive number"), mm_g_); \
} while (0)

# define CHECK_STR(label, got, exp) do { \
	const char *mm_g_ = (got); const char *mm_e_ = (exp); \
	if (!mm_g_ || !mm_e_) { \
		if (mm_g_ != mm_e_) \
			mm_fail("%s: expected %s, got %s", label, mm_show(mm_e_), mm_show(mm_g_)); \
	} else if (strcmp(mm_g_, mm_e_) != 0) \
		mm_diff(label, mm_g_, strlen(mm_g_), mm_e_, strlen(mm_e_)); \
} while (0)

# define CHECK_MEM(label, got, exp, n) do { \
	const void *mm_g_ = (got); const void *mm_e_ = (exp); size_t mm_n_ = (n); \
	if (memcmp(mm_g_, mm_e_, mm_n_) != 0) \
		mm_diff(label, mm_g_, mm_n_, mm_e_, mm_n_); \
} while (0)

# define CHECK_PTR(label, got, exp, base) do { \
	const char *mm_g_ = (const char *)(got); const char *mm_e_ = (const char *)(exp); \
	const char *mm_b_ = (const char *)(base); \
	if (mm_g_ != mm_e_) { \
		char mm_gs_[64], mm_es_[64]; \
		if (mm_g_) snprintf(mm_gs_, 64, "str + %ld", (long)(mm_g_ - mm_b_)); \
		else snprintf(mm_gs_, 64, "NULL"); \
		if (mm_e_) snprintf(mm_es_, 64, "str + %ld", (long)(mm_e_ - mm_b_)); \
		else snprintf(mm_es_, 64, "NULL"); \
		mm_fail("%s: expected %s, got %s", label, mm_es_, mm_gs_); \
	} \
} while (0)

/* captured stdout of the current case (resets the capture) */
MM_U static char	*mm_take_output(size_t *len)
{
	char	*s;

	fflush(stdout);
	s = mm_read_fd(STDOUT_FILENO, len);
	if (ftruncate(STDOUT_FILENO, 0) != 0)
		(void)0;
	lseek(STDOUT_FILENO, 0, SEEK_SET);
	mm_out_checked = 1;
	return (s);
}

# define CHECK_OUTPUT_N(exp, n) do { \
	size_t mm_len_; char *mm_out_ = mm_take_output(&mm_len_); size_t mm_n_ = (n); \
	if (mm_len_ != mm_n_ || memcmp(mm_out_, (exp), mm_n_) != 0) \
		mm_diff("output", mm_out_, mm_len_, (exp), mm_n_); \
	free(mm_out_); \
} while (0)

# define CHECK_OUTPUT(exp) do { \
	const char *mm_x_ = (exp); CHECK_OUTPUT_N(mm_x_, strlen(mm_x_)); \
} while (0)

/* ------------------------------------------------------------------------ */
/* crash description                                                        */
/* ------------------------------------------------------------------------ */

MM_U static const char	*mm_signame(int sig)
{
	if (sig == SIGSEGV)
		return ("Segmentation fault");
	if (sig == SIGBUS)
		return ("Bus error");
	if (sig == SIGABRT)
		return ("Abort (bad free()? double free?)");
	if (sig == SIGFPE)
		return ("Floating point exception (division by zero?)");
	if (sig == SIGALRM || sig == SIGKILL)
		return ("Timeout (infinite loop? too slow?)");
	return (strsignal(sig));
}

/* Turns an AddressSanitizer report into one readable line. */
MM_U static void	mm_asan_summary(const char *err, char *out, size_t cap)
{
	const char	*sum = strstr(err, "SUMMARY: AddressSanitizer: ");
	const char	*acc;
	const char	*hint = getenv("MM_SRC_DIR");
	char		kind[64] = "memory error";
	char		access[64] = "";
	char		where[256] = "";
	const char	*line;

	if (sum)
		sscanf(sum + 27, "%63s", kind);
	acc = strstr(err, "READ of size");
	if (!acc)
		acc = strstr(err, "WRITE of size");
	if (acc)
	{
		const char	*at = strstr(acc, " at ");
		int			n = (int)strcspn(acc, "\n");

		if (at && at - acc < n)
			n = (int)(at - acc);
		snprintf(access, sizeof(access), "%.*s", n, acc);
	}
	if (hint && *hint)
	{
		line = strstr(err, hint);
		if (line)
		{
			const char	*bol = line;
			const char	*in;
			const char	*file;
			int			len;

			while (bol > err && bol[-1] != '\n')
				bol--;
			in = strstr(bol, " in ");
			file = line + strlen(hint);
			while (*file == '/')
				file++;
			len = (int)strcspn(file, " \n");
			if (in && in < line)
				snprintf(where, sizeof(where), " at %.*s (%.*s)", len, file,
					(int)strcspn(in + 4, " \n"), in + 4);
			else
				snprintf(where, sizeof(where), " at %.*s", len, file);
		}
	}
	if (strcmp(kind, "SEGV") == 0)
		snprintf(out, cap, "Segmentation fault%s", where);
	else if (strcmp(kind, "stack-overflow") == 0)
		snprintf(out, cap, "stack overflow (infinite recursion?)%s", where);
	else
		snprintf(out, cap, "memory error: %s%s%s%s%s", kind,
			*access ? " (" : "", access, *access ? ")" : "", where);
}

/* ------------------------------------------------------------------------ */
/* the CASE machinery                                                       */
/* ------------------------------------------------------------------------ */

MM_U static void	mm_print_msgs(const char *msgs)
{
	const char	*p = msgs;

	while (*p)
	{
		size_t	n = strcspn(p, "\n");

		printf("        %s%.*s%s\n", MM_GREY, (int)n, p, MM_RESET);
		p += n;
		if (*p)
			p++;
	}
}

MM_U static int	mm_begin(int soft, const char *fmt, ...)
{
	va_list	ap;
	int		msgfd;
	int		errfd;
	int		outfd;
	int		st;
	int		timeout;
	pid_t	pid;
	char	*msgs;
	char	*err;
	char	crash[512] = "";
	int		ok;

	va_start(ap, fmt);
	vsnprintf(mm_desc, sizeof(mm_desc), fmt, ap);
	va_end(ap);
	timeout = mm_timeout_next ? mm_timeout_next : mm_env_int("MM_TIMEOUT", 3);
	mm_timeout_next = 0;
	fflush(stdout);
	fflush(stderr);
	msgfd = mm_tmpfd();
	errfd = mm_tmpfd();
	pid = fork();
	if (pid == 0)
	{
		outfd = mm_tmpfd();
		dup2(outfd, STDOUT_FILENO);
		close(outfd);
		dup2(errfd, STDERR_FILENO);
		mm_msg_fd = msgfd;
		mm_failed = 0;
		mm_out_checked = 0;
		setenv("MM_CUR_TIMEOUT", "", 1);
		{
			char	t[16];

			snprintf(t, sizeof(t), "%d", timeout);
			setenv("MM_CUR_TIMEOUT", t, 1);
		}
		alarm((unsigned)timeout);
		return (1);
	}
	waitpid(pid, &st, 0);
	msgs = mm_read_fd(msgfd, NULL);
	err = mm_read_fd(errfd, NULL);
	close(msgfd);
	close(errfd);
	ok = WIFEXITED(st) && WEXITSTATUS(st) == MM_EXIT_PASS;
	if (WIFSIGNALED(st))
		snprintf(crash, sizeof(crash), "crashed: %s", mm_signame(WTERMSIG(st)));
	else if (WIFEXITED(st) && WEXITSTATUS(st) == MM_ASAN_EXIT)
		mm_asan_summary(err, crash, sizeof(crash));
	else if (WIFEXITED(st) && WEXITSTATUS(st) != MM_EXIT_PASS
		&& WEXITSTATUS(st) != MM_EXIT_FAIL)
		snprintf(crash, sizeof(crash),
			"the process exited with code %d (does your code call exit()?)",
			WEXITSTATUS(st));
	if (!ok && !*crash && strstr(err, "SUMMARY: AddressSanitizer: "))
		mm_asan_summary(err, crash, sizeof(crash));
	if (soft)
	{
		if (!ok && !mm_env_int("MM_VERBOSE", 0) && mm_shown_warn >= 3)
		{
			mm_warn++;
			mm_hidden_warn++;
		}
		else if (!ok)
		{
			mm_warn++;
			mm_shown_warn++;
			printf("    %s! %s%s\n", MM_YELLOW, mm_desc, MM_RESET);
			if (*crash)
				printf("        %s%s%s\n", MM_YELLOW, crash, MM_RESET);
			mm_print_msgs(msgs);
		}
		else if (mm_env_int("MM_VERBOSE", 0))
			printf("    %s+ %s%s\n", MM_GREEN, mm_desc, MM_RESET);
	}
	else
	{
		mm_total++;
		if (ok)
		{
			mm_pass++;
			if (mm_env_int("MM_VERBOSE", 0))
				printf("    %s+ %s%s\n", MM_GREEN, mm_desc, MM_RESET);
		}
		else if (!mm_env_int("MM_VERBOSE", 0) && mm_shown >= 3)
			mm_hidden_fail++;
		else
		{
			mm_shown++;
			printf("    %sx %s%s\n", MM_RED, mm_desc, MM_RESET);
			if (*crash)
				printf("        %s%s%s\n", MM_RED, crash, MM_RESET);
			mm_print_msgs(msgs);
		}
	}
	fflush(stdout);
	free(msgs);
	free(err);
	return (0);
}

MM_U static int	mm_end(void)
{
	size_t	len;
	char	*out;

	fflush(stdout);
	if (!mm_out_checked && lseek(STDOUT_FILENO, 0, SEEK_END) > 0)
	{
		out = mm_read_fd(STDOUT_FILENO, &len);
		mm_fail("this function should not print anything, but printed %s",
			mm_showm(out, len));
	}
	_exit(mm_failed ? MM_EXIT_FAIL : MM_EXIT_PASS);
	return (0);
}

# define CASE(...) for (int mm_c_ = mm_begin(0, __VA_ARGS__); mm_c_; mm_c_ = mm_end())
# define SOFT(...) for (int mm_c_ = mm_begin(1, __VA_ARGS__); mm_c_; mm_c_ = mm_end())
# define TIMEOUT(sec) (mm_timeout_next = (sec))

/* Called at the end of main(): prints the machine-readable summary line. */
MM_U static int	mm_done(void)
{
	if (mm_hidden_fail)
		printf("    %sx ... and %d more failed case%s (mini -v shows them all)%s\n", MM_RED,
			mm_hidden_fail, mm_hidden_fail > 1 ? "s" : "", MM_RESET);
	if (mm_hidden_warn)
		printf("    %s! ... and %d more warning%s (mini -v shows them all)%s\n", MM_YELLOW,
			mm_hidden_warn, mm_hidden_warn > 1 ? "s" : "", MM_RESET);
	printf("@@RESULT %d %d %d\n", mm_pass, mm_total, mm_warn);
	return (0);
}

/* ------------------------------------------------------------------------ */
/* running the student's program (C06)                                      */
/* ------------------------------------------------------------------------ */

MM_U static int	mm_run_prog(char *const argv[])
{
	const char	*path = getenv("MM_PROG");
	int			outfd;
	int			st;
	int			t;
	pid_t		pid;

	t = mm_env_int("MM_CUR_TIMEOUT", 3);
	outfd = mm_tmpfd();
	fflush(stdout);
	pid = fork();
	if (pid == 0)
	{
		dup2(outfd, STDOUT_FILENO);
		alarm((unsigned)(t > 1 ? t - 1 : 1));
		execv(path, argv);
		_exit(127);
	}
	waitpid(pid, &st, 0);
	free(mm_prog_out);
	mm_prog_out = mm_read_fd(outfd, &mm_prog_len);
	close(outfd);
	if (WIFSIGNALED(st))
		mm_fail("your program crashed: %s", mm_signame(WTERMSIG(st)));
	else if (WEXITSTATUS(st) == MM_ASAN_EXIT)
		mm_fail("your program hit a memory error");
	return (WIFEXITED(st) ? WEXITSTATUS(st) : -1);
}

# define RUN(...) mm_run_prog((char *const[]){__VA_ARGS__, NULL})

# define CHECK_PROG_OUTPUT(exp) do { \
	const char *mm_x_ = (exp); size_t mm_n_ = strlen(mm_x_); \
	if (mm_prog_len != mm_n_ || memcmp(mm_prog_out, mm_x_, mm_n_) != 0) \
		mm_diff("output", mm_prog_out, mm_prog_len, mm_x_, mm_n_); \
} while (0)

#endif
