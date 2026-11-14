// mm:files   ft_ft.c
// mm:allowed
// mm:proto   void ft_ft(int *nbr);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	const int	start[] = {0, -1, 42, INT_MIN, INT_MAX};
	int			i;

	for (i = 0; i < 5; i++)
		CASE("x = %d; ft_ft(&x)  ->  x == 42", start[i])
		{
			int	x = start[i];

			ft_ft(&x);
			CHECK_INT("x", x, 42);
		}
	CASE("only *nbr changes (neighbouring memory untouched)")
	{
		int	arr[3] = {7, 7, 7};

		ft_ft(&arr[1]);
		CHECK(arr[0] == 7 && arr[1] == 42 && arr[2] == 7,
			"array is {%d, %d, %d}, expected {7, 42, 7}", arr[0], arr[1], arr[2]);
	}
	return (mm_done());
}
