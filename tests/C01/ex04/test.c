// mm:files   ft_ultimate_div_mod.c
// mm:allowed
// mm:proto   void ft_ultimate_div_mod(int *a, int *b);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	const int	v[][2] = {{42, 10}, {10, 42}, {0, 5}, {5, 5}, {-7, 2}, {7, -2},
		{-42, -10}, {100, 1}, {INT_MAX, 10}, {INT_MIN, 10}, {3, 5}};
	int			i;

	for (i = 0; i < (int)(sizeof(v) / sizeof(*v)); i++)
		CASE("a = %d, b = %d; ft_ultimate_div_mod(&a, &b)", v[i][0], v[i][1])
		{
			int	a = v[i][0];
			int	b = v[i][1];

			ft_ultimate_div_mod(&a, &b);
			CHECK_INT("a (the quotient)", a, v[i][0] / v[i][1]);
			CHECK_INT("b (the remainder, computed from the ORIGINAL a)", b, v[i][0] % v[i][1]);
		}
	return (mm_done());
}
