// mm:files   ft_strncpy.c
// mm:allowed
// mm:proto   char *ft_strncpy(char *dest, char *src, unsigned int n);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	struct { char *src; unsigned int n; const char *why; } t[] = {
		{"Hello", 3, "n < length: copies 3 chars, NO '\\0' added"},
		{"Hello", 5, "n == length: no '\\0' added"},
		{"Hello", 6, "n == length + 1: copies the '\\0'"},
		{"Hello", 10, "n > length: pads the rest with '\\0'"},
		{"Hello", 0, "n == 0: dest untouched"},
		{"", 4, "empty src: 4 x '\\0'"},
		{"", 0, "empty src, n == 0"},
		{"abc\0def", 7, "stops copying at '\\0' then pads"},
		{"Hello World!", 12, "longer string"},
		{"a", 16, "pads 15 bytes"},
	};
	int	i;

	for (i = 0; i < (int)(sizeof(t) / sizeof(*t)); i++)
		CASE("ft_strncpy(dest, %s, %u)  -- %s", mm_show(t[i].src), t[i].n, t[i].why)
		{
			char	dest[24];
			char	exp[24];
			char	*ret;

			memset(dest, 'X', sizeof(dest));
			memset(exp, 'X', sizeof(exp));
			strncpy(exp, t[i].src, t[i].n);
			ret = ft_strncpy(dest, t[i].src, t[i].n);
			CHECK_MEM("dest (whole buffer; 'X' = untouched)", dest, exp, sizeof(dest));
			CHECK(ret == dest, "should return dest");
		}
	CASE("does not read src past its '\\0' (src is malloc'd, n = 20)")
	{
		char	*src = strdup("short");
		char	dest[20];
		char	exp[20];

		strncpy(exp, src, 20);
		ft_strncpy(dest, src, 20);
		CHECK_MEM("dest", dest, exp, 20);
		free(src);
	}
	return (mm_done());
}
