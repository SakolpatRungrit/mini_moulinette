// mm:files   ft_div_mod.c
// mm:allowed
// mm:proto   void ft_div_mod(int a, int b, int *div, int *mod);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	const int	v[][2] = {{42, 10}, {10, 42}, {0, 5}, {5, 5}, {-42, 10}, {42, -10},
		{-42, -10}, {7, 1}, {INT_MAX, 2}, {INT_MIN, 2}, {INT_MIN, INT_MAX}, {100, 100}};
	int			i;

	for (i = 0; i < (int)(sizeof(v) / sizeof(*v)); i++)
		CASE("ft_div_mod(%d, %d, &div, &mod)", v[i][0], v[i][1])
		{
			int	d = 1234;
			int	m = 1234;

			ft_div_mod(v[i][0], v[i][1], &d, &m);
			CHECK_INT("div", d, v[i][0] / v[i][1]);
			CHECK_INT("mod", m, v[i][0] % v[i][1]);
		}
	return (mm_done());
}
