// mm:files   ft_atoi_base.c
// mm:allowed
// mm:proto   int ft_atoi_base(char *str, char *base);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	char	*dec = "0123456789";
	char	*hex = "0123456789ABCDEF";
	char	*lhex = "0123456789abcdef";
	char	*bin = "01";
	struct { char *s; char *base; int exp; } t[] = {
		{"42", dec, 42}, {"-42", dec, -42}, {"0", dec, 0}, {"2147483647", dec, INT_MAX},
		{"-2147483648", dec, INT_MIN}, {"101010", bin, 42}, {"---101", bin, -5},
		{"ff", lhex, 255}, {"FF", hex, 255}, {"FF", lhex, 0}, {"-80000000", lhex, INT_MIN},
		{"7fffffff", lhex, INT_MAX}, {"vp", "poneyvif", 40}, {"-vp", "poneyvif", -40},
		{"  \t\n\v\f\r+-+42", dec, -42}, {"  --+-+101", bin, -5}, {"101abc", bin, 5},
		{"12 3", dec, 12}, {"1012", bin, 5}, {"", dec, 0}, {"+", dec, 0}, {"-", dec, 0},
		{"- 42", dec, 0}, {"abc", dec, 0}, {"ba", "ab", 2}, {"0042", dec, 42},
		{"42", "", 0}, {"42", "4", 0}, {"42", "0123456789 ", 0}, {"42", "01\t2", 0},
		{"42", "0123+456789", 0}, {"42", "0123-456789", 0}, {"42", "01234567894", 0},
		{"42", "0\n", 0}, {"42", "0\v1", 0}, {"42", "0\f1", 0}, {"42", "0\r1", 0},
	};
	int		i;

	for (i = 0; i < (int)(sizeof(t) / sizeof(*t)); i++)
		CASE("ft_atoi_base(%s, %s)", mm_show(t[i].s), mm_show(t[i].base))
		{
			char	*s = strdup(t[i].s);
			char	*b = strdup(t[i].base);

			CHECK_INT("return value", ft_atoi_base(s, b), t[i].exp);
			free(s);
			free(b);
		}
	return (mm_done());
}
