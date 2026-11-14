// mm:files   ft_ultimate_ft.c
// mm:allowed
// mm:proto   void ft_ultimate_ft(int *********nbr);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	const int	start[] = {0, -42, INT_MAX};
	int			i;

	for (i = 0; i < 3; i++)
		CASE("x = %d; ft_ultimate_ft(&p8) with 9 levels of pointers  ->  x == 42", start[i])
		{
			int			x = start[i];
			int			*p1 = &x;
			int			**p2 = &p1;
			int			***p3 = &p2;
			int			****p4 = &p3;
			int			*****p5 = &p4;
			int			******p6 = &p5;
			int			*******p7 = &p6;
			int			********p8 = &p7;

			ft_ultimate_ft(&p8);
			CHECK_INT("x", x, 42);
			CHECK(p1 == &x && *p8 == p7, "the pointers themselves were changed");
		}
	return (mm_done());
}
