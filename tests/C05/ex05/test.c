// mm:files   ft_sqrt.c
// mm:allowed
// mm:proto   int ft_sqrt(int nb);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	struct { int n; int exp; } t[] = {
		{0, 0}, {1, 1}, {4, 2}, {9, 3}, {16, 4}, {25, 5}, {100, 10}, {144, 12},
		{1000000, 1000}, {2, 0}, {3, 0}, {5, 0}, {8, 0}, {15, 0}, {17, 0}, {99, 0},
		{-1, 0}, {-4, 0}, {INT_MIN, 0}, {2147395600, 46340}, {2147395601, 0},
		{2147483647, 0}, {2147302921, 46339},
	};
	int	i;

	for (i = 0; i < (int)(sizeof(t) / sizeof(*t)); i++)
		CASE("ft_sqrt(%d)%s", t[i].n, t[i].n > 2147000000 ? "  -- watch out for i * i overflowing" : "")
			CHECK_INT("return value", ft_sqrt(t[i].n), t[i].exp);
	return (mm_done());
}
