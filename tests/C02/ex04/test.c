// mm:files   ft_str_is_lowercase.c
// mm:allowed
// mm:proto   int ft_str_is_lowercase(char *str);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	struct { char *s; int exp; } t[] = {
		{"", 1}, {"a", 1}, {"z", 1}, {"abcdefghijklmnopqrstuvwxyz", 1}, {"hello", 1},
		{"Hello", 0}, {"hellO", 0}, {"hello world", 0}, {"hello1", 0}, {"A", 0},
		{"`", 0}, {"{", 0}, {"a`", 0}, {"z{", 0}, {"\n", 0}, {"\xe0", 0},
	};
	int	i;

	for (i = 0; i < (int)(sizeof(t) / sizeof(*t)); i++)
		CASE("ft_str_is_lowercase(%s)", mm_show(t[i].s))
		{
			char	*copy = strdup(t[i].s);

			CHECK_INT("return value", ft_str_is_lowercase(copy), t[i].exp);
			free(copy);
		}
	return (mm_done());
}
