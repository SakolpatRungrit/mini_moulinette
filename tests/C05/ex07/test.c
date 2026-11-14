// mm:files   ft_find_next_prime.c
// mm:allowed
// mm:proto   int ft_find_next_prime(int nb);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	struct { int n; int exp; } t[] = {
		{0, 2}, {1, 2}, {2, 2}, {3, 3}, {4, 5}, {8, 11}, {14, 17}, {24, 29}, {90, 97},
		{97, 97}, {7920, 7927}, {1000000, 1000003}, {-1, 2}, {-100, 2}, {INT_MIN, 2},
	};
	int	i;

	for (i = 0; i < (int)(sizeof(t) / sizeof(*t)); i++)
		CASE("ft_find_next_prime(%d)", t[i].n)
			CHECK_INT("return value", ft_find_next_prime(t[i].n), t[i].exp);
	TIMEOUT(3);
	SOFT("ft_find_next_prime(2147483647) in under 3s (INT_MAX is prime)")
		CHECK_INT("return value", ft_find_next_prime(2147483647), 2147483647);
	TIMEOUT(3);
	SOFT("ft_find_next_prime(2147483630) in under 3s")
		CHECK_INT("return value", ft_find_next_prime(2147483630), 2147483647);
	return (mm_done());
}
