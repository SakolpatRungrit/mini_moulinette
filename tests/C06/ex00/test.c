// mm:files   ft_print_program_name.c
// mm:allowed write
// mm:type    prog
#include "mm.h"

int	main(void)
{
	CASE("./ft_print_program_name  ->  \"./ft_print_program_name\\n\"")
	{
		RUN("./ft_print_program_name");
		CHECK_PROG_OUTPUT("./ft_print_program_name\n");
	}
	CASE("./a.out  ->  \"./a.out\\n\"")
	{
		RUN("./a.out");
		CHECK_PROG_OUTPUT("./a.out\n");
	}
	CASE("arguments are ignored: ./a.out hello world  ->  \"./a.out\\n\"")
	{
		RUN("./a.out", "hello", "world");
		CHECK_PROG_OUTPUT("./a.out\n");
	}
	CASE("called through a path: /home/user/my prog  ->  \"/home/user/my prog\\n\"")
	{
		RUN("/home/user/my prog");
		CHECK_PROG_OUTPUT("/home/user/my prog\n");
	}
	return (mm_done());
}
