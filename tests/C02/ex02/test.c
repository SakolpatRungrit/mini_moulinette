// mm:files   ft_str_is_alpha.c
// mm:allowed
// mm:proto   int ft_str_is_alpha(char *str);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	struct { char *s; int exp; } t[] = {
		{"", 1}, {"abc", 1}, {"ABC", 1}, {"HelloWorld", 1}, {"azAZ", 1},
		{"Hello World", 0}, {"abc1", 0}, {"1abc", 0}, {"42", 0}, {" ", 0},
		{"@", 0}, {"[", 0}, {"`", 0}, {"{", 0}, {"abc@", 0}, {"Z[", 0}, {"a`", 0},
		{"z{", 0}, {"\t", 0}, {"abc\n", 0}, {"caf\xc3\xa9", 0}, {"\x80", 0}, {"\xff", 0},
	};
	int	i;

	for (i = 0; i < (int)(sizeof(t) / sizeof(*t)); i++)
		CASE("ft_str_is_alpha(%s)", mm_show(t[i].s))
		{
			char	*copy = strdup(t[i].s);

			CHECK_INT("return value", ft_str_is_alpha(copy), t[i].exp);
			free(copy);
		}
	return (mm_done());
}
