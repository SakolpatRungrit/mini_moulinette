// mm:files   ft_show_tab.c
// mm:allowed write
#include "ft_stock_str.h"
#include "mm.h"

void	ft_show_tab(struct s_stock_str *par);

static void	test(const char *desc, char **strs, char **copies, int n)
{
	t_stock_str	*tab = malloc(sizeof(t_stock_str) * (n + 1));
	size_t		cap = 64;
	char		*exp;
	int			k = 0;
	int			i;

	for (i = 0; i < n; i++)
		cap += strlen(strs[i]) + strlen(copies[i]) + 16;
	exp = malloc(cap);
	exp[0] = '\0';
	for (i = 0; i < n; i++)
	{
		tab[i].str = strs[i];
		tab[i].copy = copies[i];
		tab[i].size = (int)strlen(strs[i]);
		k += sprintf(exp + k, "%s\n%d\n%s\n", strs[i], tab[i].size, copies[i]);
	}
	tab[n].str = 0;
	tab[n].copy = 0;
	tab[n].size = 0;
	CASE("%s", desc)
	{
		ft_show_tab(tab);
		CHECK_OUTPUT(exp);
	}
	free(tab);
	free(exp);
}

int	main(void)
{
	char	*a[] = {"hello", "world"};
	char	*big[30];
	char	*longs[1];
	char	buf[30][8];
	char	*l;
	int		i;

	test("2 elements: str, size and copy, each followed by \\n", a, a, 2);
	test("1 element", (char *[]){"solo"}, (char *[]){"solo"}, 1);
	test("empty array (first str is 0): prints nothing", NULL, NULL, 0);
	test("an empty string (size 0)", (char *[]){"", "x"}, (char *[]){"", "x"}, 2);
	test("copy differs from str (it was modified): print the copy as it is now",
		(char *[]){"original"}, (char *[]){"modified"}, 1);
	for (i = 0; i < 30; i++)
	{
		sprintf(buf[i], "w%d", i);
		big[i] = buf[i];
	}
	test("30 elements", big, big, 30);
	l = malloc(12346);
	memset(l, 'L', 12345);
	l[12345] = '\0';
	longs[0] = l;
	test("a 12345-character string (size printed with putnbr)", longs, (char *[]){"c"}, 1);
	free(l);
	return (mm_done());
}
