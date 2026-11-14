// mm:files   ft_iterative_factorial.c
// mm:allowed
// mm:proto   int ft_iterative_factorial(int nb);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	struct { int n; int exp; } t[] = {
		{0, 1}, {1, 1}, {2, 2}, {3, 6}, {5, 120}, {10, 3628800}, {12, 479001600},
		{-1, 0}, {-5, 0}, {INT_MIN, 0},
	};
	int	i;

	for (i = 0; i < (int)(sizeof(t) / sizeof(*t)); i++)
		CASE("ft_iterative_factorial(%d)", t[i].n)
			CHECK_INT("return value", ft_iterative_factorial(t[i].n), t[i].exp);
	return (mm_done());
}
