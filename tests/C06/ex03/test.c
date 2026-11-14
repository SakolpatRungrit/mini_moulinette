// mm:files   ft_sort_params.c
// mm:allowed write
// mm:type    prog
#include "mm.h"

static int	cmp(const void *a, const void *b)
{
	return (strcmp(*(char *const *)a, *(char *const *)b));
}

/* runs ./a.out with args, expects them sorted in ASCII order */
static void	test(const char *desc, char **args, int n)
{
	char	*argv[64];
	char	*sorted[64];
	char	exp[4096];
	int		k = 0;
	int		i;

	argv[0] = "./a.out";
	for (i = 0; i < n; i++)
	{
		argv[i + 1] = args[i];
		sorted[i] = args[i];
	}
	argv[n + 1] = NULL;
	qsort(sorted, n, sizeof(char *), cmp);
	exp[0] = '\0';
	for (i = 0; i < n; i++)
		k += sprintf(exp + k, "%s\n", sorted[i]);
	CASE("%s", desc)
	{
		mm_run_prog(argv);
		CHECK_PROG_OUTPUT(exp);
	}
}

int	main(void)
{
	char	*a[] = {"banana", "apple", "cherry"};
	char	*b[] = {"apple", "banana", "cherry"};
	char	*c[] = {"z", "y", "x", "w", "v"};
	char	*d[] = {"Zebra", "apple", "Apple", "zebra", "_under", "123", "~tilde"};
	char	*e[] = {"abc", "ab", "abcd", "a"};
	char	*f[] = {"same", "same", "diff", "same"};
	char	*g[] = {"b", "", "a"};
	char	*h[] = {"only"};
	char	*i_[] = {"-n", "--help", "+x", " space", "!bang"};
	char	*big[40];
	char	names[40][8];
	int		i;

	test("./a.out banana apple cherry", a, 3);
	test("./a.out apple banana cherry  (already sorted)", b, 3);
	test("./a.out z y x w v  (reverse sorted)", c, 5);
	test("./a.out Zebra apple Apple zebra _under 123 ~tilde  (ASCII order: upper < lower)", d, 7);
	test("./a.out abc ab abcd a  (prefixes come first)", e, 4);
	test("./a.out same same diff same  (duplicates are all printed)", f, 4);
	test("./a.out b \"\" a  (empty argument sorts first)", g, 3);
	test("./a.out only", h, 1);
	test("./a.out -n --help +x \" space\" !bang", i_, 5);
	CASE("./a.out  (no arguments: prints nothing)")
	{
		RUN("./a.out");
		CHECK_PROG_OUTPUT("");
	}
	srand(42);
	for (i = 0; i < 40; i++)
	{
		sprintf(names[i], "w%05d", rand() % 100000);
		big[i] = names[i];
	}
	test("./a.out with 40 random words", big, 40);
	return (mm_done());
}
