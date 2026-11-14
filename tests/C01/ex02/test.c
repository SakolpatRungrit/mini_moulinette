// mm:files   ft_swap.c
// mm:allowed
// mm:proto   void ft_swap(int *a, int *b);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	const int	v[][2] = {{1, 2}, {42, -42}, {0, 0}, {5, 5}, {INT_MIN, INT_MAX},
		{0, INT_MIN}, {-1, 1}};
	int			i;

	for (i = 0; i < (int)(sizeof(v) / sizeof(*v)); i++)
		CASE("a = %d, b = %d; ft_swap(&a, &b)", v[i][0], v[i][1])
		{
			int	a = v[i][0];
			int	b = v[i][1];

			ft_swap(&a, &b);
			CHECK_INT("a", a, v[i][1]);
			CHECK_INT("b", b, v[i][0]);
		}
	CASE("swapping twice gives back the original values")
	{
		int	a = 13;
		int	b = 37;

		ft_swap(&a, &b);
		ft_swap(&a, &b);
		CHECK(a == 13 && b == 37, "got a = %d, b = %d", a, b);
	}
	SOFT("ft_swap(&a, &a) leaves a unchanged (breaks the XOR-swap trick)")
	{
		int	a = 42;

		ft_swap(&a, &a);
		CHECK_INT("a", a, 42);
	}
	return (mm_done());
}
