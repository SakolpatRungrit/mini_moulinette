// mm:files   ft_str_is_printable.c
// mm:allowed
// mm:proto   int ft_str_is_printable(char *str);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	struct { char *s; int exp; } t[] = {
		{"", 1}, {" ", 1}, {"~", 1}, {"Hello World!", 1}, {"!\"#$%&'()*+,-./0123456789", 1},
		{"\t", 0}, {"\n", 0}, {"hello\n", 0}, {"\x1f", 0}, {"\x7f", 0}, {"abc\x7f", 0},
		{"\x01", 0}, {"\x80", 0}, {"\xff", 0}, {"caf\xc3\xa9", 0},
	};
	char	all[96];
	int		i;

	for (i = 0; i < (int)(sizeof(t) / sizeof(*t)); i++)
		CASE("ft_str_is_printable(%s)", mm_show(t[i].s))
		{
			char	*copy = strdup(t[i].s);

			CHECK_INT("return value", ft_str_is_printable(copy), t[i].exp);
			free(copy);
		}
	for (i = 0; i < 95; i++)
		all[i] = (char)(32 + i);
	all[95] = '\0';
	CASE("every char from ' ' (32) to '~' (126) is printable")
	{
		CHECK_INT("return value", ft_str_is_printable(all), 1);
	}
	return (mm_done());
}
