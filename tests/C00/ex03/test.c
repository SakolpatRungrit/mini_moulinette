// mm:files   ft_print_numbers.c
// mm:allowed write
// mm:proto   void ft_print_numbers(void);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	CASE("ft_print_numbers() prints 0..9 with no newline")
	{
		ft_print_numbers();
		CHECK_OUTPUT("0123456789");
	}
	CASE("calling it twice prints it twice (no hidden state)")
	{
		ft_print_numbers();
		ft_print_numbers();
		CHECK_OUTPUT("01234567890123456789");
	}
	return (mm_done());
}
