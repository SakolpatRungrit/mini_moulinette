// mm:files   ft_boolean.h
// mm:type    header
#include "ft_boolean.h"
#include "ft_boolean.h"

/* --- the subject's main, unchanged (it must compile with only ft_boolean.h,
       so the header has to include <unistd.h> itself) --- */
void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

t_bool	ft_is_even(int nbr)
{
	return ((EVEN(nbr)) ? TRUE : FALSE);
}

int	subject_main(int argc, char **argv)
{
	(void)argv;
	if (ft_is_even(argc - 1) == TRUE)
		ft_putstr(EVEN_MSG);
	else
		ft_putstr(ODD_MSG);
	return (SUCCESS);
}
/* ----------------------------------------------------------------------- */

#include "mm.h"

int	main(void)
{
	int	argc;

	CASE("TRUE == 1, FALSE == 0, SUCCESS == 0")
	{
		CHECK_INT("TRUE", TRUE, 1);
		CHECK_INT("FALSE", FALSE, 0);
		CHECK_INT("SUCCESS", SUCCESS, 0);
	}
	CASE("t_bool is an int-like type")
	{
		t_bool	b = TRUE;

		CHECK(sizeof(t_bool) == sizeof(int), "t_bool should be a typedef of int");
		CHECK_INT("b", b, 1);
	}
	for (argc = 1; argc <= 4; argc++)
		CASE("the subject's main with %d argument(s)", argc - 1)
		{
			CHECK_INT("return value", subject_main(argc, NULL), 0);
			CHECK_OUTPUT((argc - 1) % 2 == 0 ? "I have an even number of arguments.\n"
				: "I have an odd number of arguments.\n");
		}
	CASE("EVEN(n) for n = -3..4")
	{
		int	n;

		for (n = -3; n <= 4; n++)
			CHECK(!!(EVEN(n)) == (n % 2 == 0), "EVEN(%d) gave %d", n, EVEN(n));
	}
	SOFT("EVEN(1 + 1) is true  -- put parentheses around the macro argument")
		CHECK(EVEN(1 + 1), "EVEN(1 + 1) is false: write ((nbr) %% 2 == 0)");
	return (mm_done());
}
