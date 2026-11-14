// mm:files   ft_rev_int_tab.c
// mm:allowed
// mm:proto   void ft_rev_int_tab(int *tab, int size);
#include "mm.h"
#include "proto.h"

static const char	*show_tab(const int *t, int n)
{
	static char	buf[2][512];
	static int	slot;
	char		*b = buf[slot++ % 2];
	int			k = 0;
	int			i;

	k += sprintf(b + k, "{");
	for (i = 0; i < n && k < 480; i++)
		k += sprintf(b + k, "%s%d", i ? ", " : "", t[i]);
	sprintf(b + k, "%s}", i < n ? ", ..." : "");
	return (b);
}

static void	test(const int *src, int n)
{
	int	*tab = malloc(sizeof(int) * (n ? n : 1));
	int	*exp = malloc(sizeof(int) * (n ? n : 1));
	int	i;

	for (i = 0; i < n; i++)
	{
		tab[i] = src[i];
		exp[i] = src[n - 1 - i];
	}
	CASE("ft_rev_int_tab(%s, %d)", show_tab(src, n), n)
	{
		ft_rev_int_tab(tab, n);
		CHECK(memcmp(tab, exp, sizeof(int) * n) == 0, "expected %s\ngot      %s",
			show_tab(exp, n), show_tab(tab, n));
	}
	free(tab);
	free(exp);
}

int	main(void)
{
	const int	a[] = {1, 2, 3, 4, 5};
	const int	b[] = {1, 2, 3, 4, 5, 6};
	const int	c[] = {42};
	const int	d[] = {1, 2};
	const int	e[] = {-5, 0, INT_MIN, INT_MAX, 7, 7, -1};
	int			big[1001];
	int			i;

	test(a, 5);
	test(b, 6);
	test(c, 1);
	test(d, 2);
	test(e, 7);
	for (i = 0; i < 1001; i++)
		big[i] = i * 3 - 500;
	test(big, 1001);
	SOFT("ft_rev_int_tab(tab, 0) does nothing and doesn't crash")
	{
		int	one = 7;

		ft_rev_int_tab(&one, 0);
		CHECK_INT("tab[0]", one, 7);
	}
	return (mm_done());
}
