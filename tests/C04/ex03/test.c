// mm:files   ft_atoi.c
// mm:allowed
// mm:proto   int ft_atoi(char *str);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	struct { char *s; int exp; } t[] = {
		{"42", 42}, {"-42", -42}, {"0", 0}, {"-0", 0}, {"+42", 42},
		{" ---+--+1234ab567", -1234},
		{"   42", 42}, {"\t\n\v\f\r 42", 42}, {"\t\n\v\f\r -42", -42},
		{"--42", 42}, {"---42", -42}, {"+-+-+42", 42}, {"-+-+-42", -42},
		{"42abc", 42}, {"42 43", 42}, {"0042", 42}, {"-0042", -42},
		{"2147483647", 2147483647}, {"-2147483648", INT_MIN}, {"+2147483647", INT_MAX},
		{"", 0}, {"   ", 0}, {"-", 0}, {"+", 0}, {"+-", 0}, {"abc", 0}, {"a42", 0},
		{"- 42", 0}, {"+ 42", 0}, {"\x01 42", 0}, {"\x1b 42", 0}, {"*42", 0},
		{"1", 1}, {"9", 9}, {"10", 10}, {"1000000000", 1000000000},
	};
	int	i;

	for (i = 0; i < (int)(sizeof(t) / sizeof(*t)); i++)
		CASE("ft_atoi(%s)", mm_show(t[i].s))
		{
			char	*s = strdup(t[i].s);

			CHECK_INT("return value", ft_atoi(s), t[i].exp);
			CHECK_STR("the string itself (must not be modified)", s, t[i].s);
			free(s);
		}
	SOFT("ft_atoi(\"99999999999999999999\")  -- overflow is undefined, just don't crash")
		ft_atoi("99999999999999999999");
	SOFT("ft_atoi(\"--------------------------------------------------1\") many signs")
		CHECK_INT("return value", ft_atoi("--------------------------------------------------1"), 1);
	return (mm_done());
}
