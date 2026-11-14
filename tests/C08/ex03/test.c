// mm:files   ft_point.h
// mm:type    header
#include "ft_point.h"
#include "ft_point.h"
#include "mm.h"

/* the subject's code */
void	set_point(t_point *point)
{
	point->x = 42;
	point->y = 21;
}

int	main(void)
{
	CASE("the subject's main: set_point(&point) gives x = 42, y = 21")
	{
		t_point	point;

		set_point(&point);
		CHECK_INT("point.x", point.x, 42);
		CHECK_INT("point.y", point.y, 21);
	}
	CASE("t_point is a typedef of struct s_point")
	{
		struct s_point	p;
		t_point			*q = &p;

		q->x = -1;
		q->y = INT_MAX;
		CHECK(p.x == -1 && p.y == INT_MAX, "x and y should be ints");
	}
	return (mm_done());
}
