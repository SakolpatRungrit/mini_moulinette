// mm:files   ft_print_comb.c
// mm:allowed write
// mm:proto   void ft_print_comb(void);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	char	exp[1024];
	int		k = 0;
	int		a;
	int		b;
	int		c;

	for (a = 0; a <= 7; a++)
		for (b = a + 1; b <= 8; b++)
			for (c = b + 1; c <= 9; c++)
			{
				if (k > 0)
					k += sprintf(exp + k, ", ");
				k += sprintf(exp + k, "%d%d%d", a, b, c);
			}
	CASE("ft_print_comb() prints 012, 013, ..., 789")
	{
		ft_print_comb();
		CHECK_OUTPUT(exp);
	}
	CASE("output starts with \"012, 013\" and ends with \"789\" (no trailing comma)")
	{
		size_t	len;
		char	*out;

		ft_print_comb();
		out = mm_take_output(&len);
		CHECK(len >= 8 && strncmp(out, "012, 013", 8) == 0, "starts with %s", mm_showm(out, len < 10 ? len : 10));
		CHECK(len >= 3 && strcmp(out + len - 3, "789") == 0, "ends with %s", mm_show(len >= 5 ? out + len - 5 : out));
	}
	return (mm_done());
}
