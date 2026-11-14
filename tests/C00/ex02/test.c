// mm:files   ft_print_reverse_alphabet.c
// mm:allowed write
// mm:proto   void ft_print_reverse_alphabet(void);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	CASE("ft_print_reverse_alphabet() prints z..a with no newline")
	{
		ft_print_reverse_alphabet();
		CHECK_OUTPUT("zyxwvutsrqponmlkjihgfedcba");
	}
	CASE("calling it twice prints it twice (no hidden state)")
	{
		ft_print_reverse_alphabet();
		ft_print_reverse_alphabet();
		CHECK_OUTPUT("zyxwvutsrqponmlkjihgfedcbazyxwvutsrqponmlkjihgfedcba");
	}
	return (mm_done());
}
