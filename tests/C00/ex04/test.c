// mm:files   ft_is_negative.c
// mm:allowed write
// mm:proto   void ft_is_negative(int n);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	const int	n[] = {-1, 1, 0, -42, 42, INT_MIN, INT_MAX, -2147483647};
	int			i;

	for (i = 0; i < (int)(sizeof(n) / sizeof(*n)); i++)
		CASE("ft_is_negative(%d)", n[i])
		{
			ft_is_negative(n[i]);
			CHECK_OUTPUT(n[i] < 0 ? "N" : "P");
		}
	CASE("0 counts as positive: prints 'P' (no newline)")
	{
		ft_is_negative(0);
		ft_is_negative(-0);
		CHECK_OUTPUT("PP");
	}
	return (mm_done());
}
