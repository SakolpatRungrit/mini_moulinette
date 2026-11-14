// mm:files   ft_strncat.c
// mm:allowed
// mm:proto   char *ft_strncat(char *dest, char *src, unsigned int nb);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	struct { char *d; char *s; unsigned int nb; } t[] = {
		{"Hello", " World", 6}, {"Hello", " World", 3}, {"Hello", " World", 0},
		{"Hello", " World", 100}, {"", "abc", 2}, {"", "abc", 3}, {"abc", "", 5},
		{"", "", 1}, {"ab", "cdef", 1}, {"x", "yz\0hidden", 9},
	};
	int	i;

	for (i = 0; i < (int)(sizeof(t) / sizeof(*t)); i++)
		CASE("dest = %s; ft_strncat(dest, %s, %u)", mm_show(t[i].d), mm_show(t[i].s), t[i].nb)
		{
			char	dest[32];
			char	exp[32];
			char	*src = strdup(t[i].s);
			char	*ret;

			memset(dest, 'X', sizeof(dest));
			memset(exp, 'X', sizeof(exp));
			strcpy(dest, t[i].d);
			strcpy(exp, t[i].d);
			strncat(exp, t[i].s, t[i].nb);
			ret = ft_strncat(dest, src, t[i].nb);
			CHECK_MEM("dest (whole buffer; 'X' = untouched)", dest, exp, sizeof(dest));
			CHECK(ret == dest, "should return dest");
			free(src);
		}
	CASE("always adds the '\\0' after the copied part")
	{
		char	dest[16];

		memset(dest, 'X', sizeof(dest));
		strcpy(dest, "ab");
		ft_strncat(dest, "cdef", 2);
		CHECK_MEM("dest", dest, "abcd\0XXX", 8);
	}
	return (mm_done());
}
