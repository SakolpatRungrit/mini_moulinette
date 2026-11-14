// mm:files   ft_iterative_power.c
// mm:allowed
// mm:proto   int ft_iterative_power(int nb, int power);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	struct { int nb; int p; int exp; } t[] = {
		{2, 10, 1024}, {3, 3, 27}, {5, 1, 5}, {5, 0, 1}, {0, 0, 1}, {0, 5, 0},
		{-2, 3, -8}, {-2, 4, 16}, {-1, 1001, -1}, {1, 1000000, 1}, {2, 30, 1073741824},
		{-2, 31, INT_MIN}, {7, -1, 0}, {0, -1, 0}, {2, INT_MIN, 0}, {46340, 2, 2147395600},
		{10, 9, 1000000000},
	};
	int	i;

	for (i = 0; i < (int)(sizeof(t) / sizeof(*t)); i++)
		CASE("ft_iterative_power(%d, %d)", t[i].nb, t[i].p)
			CHECK_INT("return value", ft_iterative_power(t[i].nb, t[i].p), t[i].exp);
	return (mm_done());
}
