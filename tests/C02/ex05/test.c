// mm:files   ft_str_is_uppercase.c
// mm:allowed
// mm:proto   int ft_str_is_uppercase(char *str);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	struct { char *s; int exp; } t[] = {
		{"", 1}, {"A", 1}, {"Z", 1}, {"ABCDEFGHIJKLMNOPQRSTUVWXYZ", 1}, {"HELLO", 1},
		{"Hello", 0}, {"HELLo", 0}, {"HELLO WORLD", 0}, {"HELLO1", 0}, {"a", 0},
		{"@", 0}, {"[", 0}, {"A@", 0}, {"Z[", 0}, {"\n", 0}, {"\xc0", 0},
	};
	int	i;

	for (i = 0; i < (int)(sizeof(t) / sizeof(*t)); i++)
		CASE("ft_str_is_uppercase(%s)", mm_show(t[i].s))
		{
			char	*copy = strdup(t[i].s);

			CHECK_INT("return value", ft_str_is_uppercase(copy), t[i].exp);
			free(copy);
		}
	return (mm_done());
}
