// mm:files   ft_str_is_numeric.c
// mm:allowed
// mm:proto   int ft_str_is_numeric(char *str);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	struct { char *s; int exp; } t[] = {
		{"", 1}, {"0", 1}, {"9", 1}, {"0123456789", 1}, {"42", 1},
		{"-42", 0}, {"+42", 0}, {"4 2", 0}, {"42a", 0}, {"a42", 0}, {"/", 0},
		{":", 0}, {"0/", 0}, {"9:", 0}, {" ", 0}, {"\t42", 0}, {"\x80", 0}, {"\xb2", 0},
	};
	int	i;

	for (i = 0; i < (int)(sizeof(t) / sizeof(*t)); i++)
		CASE("ft_str_is_numeric(%s)", mm_show(t[i].s))
		{
			char	*copy = strdup(t[i].s);

			CHECK_INT("return value", ft_str_is_numeric(copy), t[i].exp);
			free(copy);
		}
	return (mm_done());
}
