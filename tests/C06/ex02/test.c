// mm:files   ft_rev_params.c
// mm:allowed write
// mm:type    prog
#include "mm.h"

int	main(void)
{
	CASE("./a.out hello world 42")
	{
		RUN("./a.out", "hello", "world", "42");
		CHECK_PROG_OUTPUT("42\nworld\nhello\n");
	}
	CASE("./a.out  (no arguments: prints nothing, not even the program name)")
	{
		RUN("./a.out");
		CHECK_PROG_OUTPUT("");
	}
	CASE("./a.out one")
	{
		RUN("./a.out", "one");
		CHECK_PROG_OUTPUT("one\n");
	}
	CASE("./a.out \"\" x \"\"")
	{
		RUN("./a.out", "", "x", "");
		CHECK_PROG_OUTPUT("\nx\n\n");
	}
	CASE("./a.out \"with spaces\" b")
	{
		RUN("./a.out", "with spaces", "b");
		CHECK_PROG_OUTPUT("b\nwith spaces\n");
	}
	CASE("./a.out 0 1 2 ... 99 (100 arguments)")
	{
		char	*args[102];
		char	exp[1000];
		char	names[100][4];
		int		i;
		int		k = 0;

		args[0] = "./a.out";
		for (i = 0; i < 100; i++)
		{
			sprintf(names[i], "%d", i);
			args[i + 1] = names[i];
		}
		for (i = 99; i >= 0; i--)
			k += sprintf(exp + k, "%d\n", i);
		args[101] = NULL;
		mm_run_prog(args);
		CHECK_PROG_OUTPUT(exp);
	}
	return (mm_done());
}
