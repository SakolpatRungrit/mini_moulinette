// mm:files   ft_is_prime.c
// mm:allowed
// mm:proto   int ft_is_prime(int nb);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	struct { int n; int exp; } t[] = {
		{0, 0}, {1, 0}, {2, 1}, {3, 1}, {4, 0}, {5, 1}, {9, 0}, {13, 1}, {25, 0},
		{97, 1}, {100, 0}, {7919, 1}, {7921, 0}, {1000003, 1}, {1000001, 0},
		{-1, 0}, {-2, 0}, {-7, 0}, {INT_MIN, 0}, {2147483646, 0},
	};
	int	i;

	for (i = 0; i < (int)(sizeof(t) / sizeof(*t)); i++)
		CASE("ft_is_prime(%d)", t[i].n)
			CHECK_INT("return value", ft_is_prime(t[i].n), t[i].exp);
	TIMEOUT(3);
	SOFT("ft_is_prime(2147483647) in under 3s  -- stop at sqrt(nb), and beware i * i overflow")
		CHECK_INT("return value", ft_is_prime(2147483647), 1);
	TIMEOUT(3);
	SOFT("ft_is_prime(2147483629) in under 3s (the 2nd-largest prime that fits in an int)")
		CHECK_INT("return value", ft_is_prime(2147483629), 1);
	return (mm_done());
}
