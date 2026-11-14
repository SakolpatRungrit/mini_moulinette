// mm:files   ft_print_alphabet.c
// mm:allowed write
// mm:proto   void ft_print_alphabet(void);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	CASE("ft_print_alphabet() prints a..z with no newline")
	{
		ft_print_alphabet();
		CHECK_OUTPUT("abcdefghijklmnopqrstuvwxyz");
	}
	CASE("calling it twice prints it twice (no hidden state)")
	{
		ft_print_alphabet();
		ft_print_alphabet();
		CHECK_OUTPUT("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz");
	}
	return (mm_done());
}
