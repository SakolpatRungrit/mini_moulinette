// mm:files   ft_putchar.c
// mm:allowed write
// mm:proto   void ft_putchar(char c);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	const char	chars[] = "aZ0 ~\n\t";
	int			i;

	for (i = 0; chars[i]; i++)
		CASE("ft_putchar(%s)", mm_showm(&chars[i], 1))
		{
			ft_putchar(chars[i]);
			CHECK_OUTPUT_N(&chars[i], 1);
		}
	CASE("ft_putchar('\\0') writes exactly one byte")
	{
		ft_putchar('\0');
		CHECK_OUTPUT_N("\0", 1);
	}
	CASE("ft_putchar(127) and ft_putchar(-1): any byte is printed as-is")
	{
		ft_putchar(127);
		ft_putchar((char)0xff);
		CHECK_OUTPUT_N("\x7f\xff", 2);
	}
	CASE("three calls in a row: 4, 2, \\n")
	{
		ft_putchar('4');
		ft_putchar('2');
		ft_putchar('\n');
		CHECK_OUTPUT("42\n");
	}
	return (mm_done());
}
