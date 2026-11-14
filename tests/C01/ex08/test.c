// mm:files   ft_sort_int_tab.c
// mm:allowed
// mm:proto   void ft_sort_int_tab(int *tab, int size);
#include "mm.h"
#include "proto.h"

static int	cmp(const void *a, const void *b)
{
	int	x = *(const int *)a;
	int	y = *(const int *)b;

	return ((x > y) - (x < y));
}

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

static void	test(const char *what, const int *src, int n)
{
	int	*tab = malloc(sizeof(int) * (n ? n : 1));
	int	*exp = malloc(sizeof(int) * (n ? n : 1));

	memcpy(tab, src, sizeof(int) * n);
	memcpy(exp, src, sizeof(int) * n);
	qsort(exp, n, sizeof(int), cmp);
	CASE("%s: %s", what, show_tab(src, n))
	{
		ft_sort_int_tab(tab, n);
		CHECK(memcmp(tab, exp, sizeof(int) * n) == 0, "expected %s\ngot      %s",
			show_tab(exp, n), show_tab(tab, n));
	}
	free(tab);
	free(exp);
}

int	main(void)
{
	const int	a[] = {5, 2, 9, 1, 7};
	const int	b[] = {1, 2, 3, 4, 5};
	const int	c[] = {5, 4, 3, 2, 1};
	const int	d[] = {3, 1, 3, 1, 3, 1};
	const int	e[] = {42};
	const int	f[] = {2, 1};
	const int	g[] = {INT_MAX, INT_MIN, 0, -1, 1, INT_MIN, INT_MAX};
	const int	h[] = {-10, -20, -30, 0, 10};
	int			big[500];
	int			i;

	test("random", a, 5);
	test("already sorted", b, 5);
	test("reverse sorted", c, 5);
	test("duplicates", d, 6);
	test("one element", e, 1);
	test("two elements", f, 2);
	test("INT_MIN / INT_MAX (no overflow when comparing)", g, 7);
	test("negatives", h, 5);
	srand(42);
	for (i = 0; i < 500; i++)
		big[i] = rand() % 2001 - 1000;
	test("500 random numbers", big, 500);
	SOFT("ft_sort_int_tab(tab, 0) does nothing and doesn't crash")
	{
		int	one = 7;

		ft_sort_int_tab(&one, 0);
		CHECK_INT("tab[0]", one, 7);
	}
	return (mm_done());
}
