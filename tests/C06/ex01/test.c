// mm:files   ft_print_params.c
// mm:allowed write
// mm:type    prog
#include "mm.h"

int	main(void)
{
	CASE("./a.out hello world 42")
	{
		RUN("./a.out", "hello", "world", "42");
		CHECK_PROG_OUTPUT("hello\nworld\n42\n");
	}
	CASE("./a.out  (no arguments: prints nothing)")
	{
		RUN("./a.out");
		CHECK_PROG_OUTPUT("");
	}
	CASE("./a.out one")
	{
		RUN("./a.out", "one");
		CHECK_PROG_OUTPUT("one\n");
	}
	CASE("./a.out \"\"  (an empty argument is still a line)")
	{
		RUN("./a.out", "");
		CHECK_PROG_OUTPUT("\n");
	}
	CASE("./a.out \"with spaces\" \"\\ttab\" \"-n\"")
	{
		RUN("./a.out", "with spaces", "\ttab", "-n");
		CHECK_PROG_OUTPUT("with spaces\n\ttab\n-n\n");
	}
	CASE("./a.out a b c ... (100 arguments)")
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
			k += sprintf(exp + k, "%d\n", i);
		}
		args[101] = NULL;
		mm_run_prog(args);
		CHECK_PROG_OUTPUT(exp);
	}
	return (mm_done());
}
