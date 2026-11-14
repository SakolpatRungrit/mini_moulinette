// mm:files   ft_putnbr.c
// mm:allowed write
// mm:proto   void ft_putnbr(int nb);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	const int	n[] = {0, 1, -1, 9, 10, -10, 42, -42, 100, -100, 1000000000,
		123456789, -987654321, INT_MAX, INT_MIN, INT_MIN + 1, INT_MAX - 1};
	char		exp[32];
	int			i;

	for (i = 0; i < (int)(sizeof(n) / sizeof(*n)); i++)
	{
		sprintf(exp, "%d", n[i]);
		CASE("ft_putnbr(%d)", n[i])
		{
			ft_putnbr(n[i]);
			CHECK_OUTPUT(exp);
		}
	}
	CASE("two calls in a row: ft_putnbr(-5); ft_putnbr(5)")
	{
		ft_putnbr(-5);
		ft_putnbr(5);
		CHECK_OUTPUT("-55");
	}
	return (mm_done());
}
