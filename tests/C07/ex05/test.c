// mm:files   ft_split.c
// mm:allowed malloc
// mm:proto   char **ft_split(char *str, char *charset);
#include "mm.h"
#include "proto.h"

static const char	*show_words(char **w)
{
	static char	buf[1024];
	int			k = 0;
	int			i;

	if (!w)
		return ("NULL");
	k += sprintf(buf + k, "{");
	for (i = 0; w[i] && k < 900; i++)
		k += sprintf(buf + k, "%s, ", mm_show(w[i]));
	sprintf(buf + k, "%sNULL}", w[i] ? "..., " : "");
	return (buf);
}

static void	test(char *str, char *charset, char **exp)
{
	char	*e_desc = strdup(show_words(exp));

	CASE("ft_split(%s, %s)", mm_show(str), mm_show(charset))
	{
		char	*s = strdup(str);
		char	*cs = strdup(charset);
		char	**r = ft_split(s, cs);
		int		i;
		int		same = (r != NULL);

		for (i = 0; same && exp[i]; i++)
			if (!r[i] || strcmp(r[i], exp[i]) != 0)
				same = 0;
		if (same && r[i] != NULL)
			same = 0;
		if (!same)
			mm_fail("expected %s\ngot      %s", e_desc, show_words(r));
		for (i = 0; r && r[i]; i++)
			free(r[i]);
		free(r);
		free(s);
		free(cs);
	}
	free(e_desc);
}

int	main(void)
{
	test("hello world 42", " ", (char *[]){"hello", "world", "42", NULL});
	test("  leading and trailing  ", " ", (char *[]){"leading", "and", "trailing", NULL});
	test("a,b;;c", ",;", (char *[]){"a", "b", "c", NULL});
	test("xxaxxbxx", "x", (char *[]){"a", "b", NULL});
	test("no-separator-here", " ", (char *[]){"no-separator-here", NULL});
	test("a\tb\nc", "\t\n", (char *[]){"a", "b", "c", NULL});
	test("one", "", (char *[]){"one", NULL});
	test("a b", "", (char *[]){"a b", NULL});
	test("", " ", (char *[]){NULL});
	test("", "", (char *[]){NULL});
	test("     ", " ", (char *[]){NULL});
	test("one", "one", (char *[]){NULL});
	test("x", " ", (char *[]){"x", NULL});
	test("abcabc", "b", (char *[]){"a", "ca", "c", NULL});
	test("charset  with  repeats", "  ", (char *[]){"charset", "with", "repeats", NULL});
	test("The quick brown fox", "aeiou", (char *[]){"Th", " q", "ck br", "wn f", "x", NULL});
	return (mm_done());
}
