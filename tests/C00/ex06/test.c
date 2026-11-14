// mm:files   ft_print_comb2.c
// mm:allowed write
// mm:proto   void ft_print_comb2(void);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	static char	exp[40000];
	int			k = 0;
	int			a;
	int			b;

	for (a = 0; a <= 98; a++)
		for (b = a + 1; b <= 99; b++)
		{
			if (k > 0)
				k += sprintf(exp + k, ", ");
			k += sprintf(exp + k, "%02d %02d", a, b);
		}
	CASE("ft_print_comb2() prints 00 01, 00 02, ..., 98 99")
	{
		ft_print_comb2();
		CHECK_OUTPUT(exp);
	}
	CASE("numbers below 10 keep their leading zero (\"00 09, 00 10\")")
	{
		size_t	len;
		char	*out;

		ft_print_comb2();
		out = mm_take_output(&len);
		CHECK(strstr(out, "00 09, 00 10") != NULL, "\"00 09, 00 10\" not found in your output");
		CHECK(len >= 5 && strcmp(out + len - 5, "98 99") == 0, "should end with \"98 99\" (no trailing comma)");
	}
	return (mm_done());
}
