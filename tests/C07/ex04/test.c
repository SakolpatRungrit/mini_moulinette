// mm:files   ft_convert_base.c ft_convert_base2.c
// mm:allowed malloc free
// mm:proto   char *ft_convert_base(char *nbr, char *base_from, char *base_to);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	char	*dec = "0123456789";
	char	*hex = "0123456789ABCDEF";
	char	*lhex = "0123456789abcdef";
	char	*bin = "01";
	char	*pony = "poneyvif";
	struct { char *n; char *from; char *to; char *exp; } t[] = {
		{"42", dec, bin, "101010"}, {"-42", dec, hex, "-2A"}, {"101010", bin, dec, "42"},
		{"ff", lhex, dec, "255"}, {"0", dec, bin, "0"}, {"-0", dec, dec, "0"},
		{"2147483647", dec, hex, "7FFFFFFF"}, {"-2147483648", dec, dec, "-2147483648"},
		{"-2147483648", dec, bin, "-10000000000000000000000000000000"},
		{"-80000000", lhex, dec, "-2147483648"}, {"  --+-ff", lhex, dec, "-255"},
		{" \t\n\v\f\r42", dec, dec, "42"}, {"12abc", dec, dec, "12"}, {"", dec, dec, "0"},
		{"abc", dec, dec, "0"}, {"vp", pony, dec, "40"}, {"40", dec, pony, "vp"},
		{"42", dec, "ab", "bababa"}, {"7", dec, dec, "7"}, {"0042", dec, hex, "2A"},
	};
	struct { char *from; char *to; } bad[] = {
		{"", dec}, {"0", dec}, {"00", dec}, {"01+", dec}, {"-01", dec}, {"0 1", dec},
		{"0\t1", dec}, {dec, ""}, {dec, "1"}, {dec, "0110"}, {dec, "ab+"}, {dec, "a-b"},
		{dec, "a b"}, {dec, "a\nb"},
	};
	int		i;

	for (i = 0; i < (int)(sizeof(t) / sizeof(*t)); i++)
		CASE("ft_convert_base(%s, %s, %s)", mm_show(t[i].n), mm_show(t[i].from), mm_show(t[i].to))
		{
			char	*r = ft_convert_base(t[i].n, t[i].from, t[i].to);

			CHECK_STR("result", r, t[i].exp);
			free(r);
		}
	for (i = 0; i < (int)(sizeof(bad) / sizeof(*bad)); i++)
		CASE("ft_convert_base(\"42\", %s, %s)  -- invalid base: NULL", mm_show(bad[i].from),
			mm_show(bad[i].to))
			CHECK_STR("result", ft_convert_base("42", bad[i].from, bad[i].to), NULL);
	return (mm_done());
}
