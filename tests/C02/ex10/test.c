// mm:files   ft_strlcpy.c
// mm:allowed
// mm:proto   unsigned int ft_strlcpy(char *dest, char *src, unsigned int size);
#include "mm.h"
#include "proto.h"

/* BSD strlcpy */
static unsigned int	ref(char *dest, const char *src, unsigned int size)
{
	unsigned int	len = (unsigned int)strlen(src);
	unsigned int	i;

	if (size > 0)
	{
		for (i = 0; i + 1 < size && src[i]; i++)
			dest[i] = src[i];
		dest[i] = '\0';
	}
	return (len);
}

int	main(void)
{
	char			*srcs[] = {"Hello", "", "Hello World!"};
	unsigned int	sizes[] = {0, 1, 2, 5, 6, 7, 12, 13, 20};
	int				i;
	int				j;

	for (i = 0; i < 3; i++)
		for (j = 0; j < 9; j++)
			CASE("ft_strlcpy(dest, %s, %u)", mm_show(srcs[i]), sizes[j])
			{
				char			dest[24];
				char			exp[24];
				char			*src = strdup(srcs[i]);
				unsigned int	r;

				memset(dest, 'X', sizeof(dest));
				memset(exp, 'X', sizeof(exp));
				ref(exp, src, sizes[j]);
				r = ft_strlcpy(dest, src, sizes[j]);
				CHECK_INT("return value (always strlen(src))", r, strlen(src));
				CHECK_MEM("dest (whole buffer; 'X' = untouched)", dest, exp, sizeof(dest));
				free(src);
			}
	CASE("size 0 must not write anything, not even '\\0'")
	{
		char	dest[4] = "abc";

		CHECK_INT("return value", ft_strlcpy(dest, "xyz", 0), 3);
		CHECK_STR("dest", dest, "abc");
	}
	return (mm_done());
}
