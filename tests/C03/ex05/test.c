// mm:files   ft_strlcat.c
// mm:allowed
// mm:proto   unsigned int ft_strlcat(char *dest, char *src, unsigned int size);
#include "mm.h"
#include "proto.h"

/* BSD strlcat */
static unsigned int	ref(char *dest, const char *src, unsigned int size)
{
	unsigned int	dlen = 0;
	unsigned int	slen = (unsigned int)strlen(src);
	unsigned int	i;

	while (dlen < size && dest[dlen])
		dlen++;
	if (dlen == size)
		return (size + slen);
	for (i = 0; src[i] && dlen + i + 1 < size; i++)
		dest[dlen + i] = src[i];
	dest[dlen + i] = '\0';
	return (dlen + slen);
}

int	main(void)
{
	char			*pairs[][2] = {{"Hello", " World"}, {"", "abc"}, {"abc", ""}, {"Hi", "!"}};
	unsigned int	sizes[] = {0, 1, 3, 5, 6, 7, 9, 11, 12, 13, 20, 32};
	int				i;
	int				j;

	for (i = 0; i < 4; i++)
		for (j = 0; j < 12; j++)
			CASE("dest = %s; ft_strlcat(dest, %s, %u)", mm_show(pairs[i][0]),
				mm_show(pairs[i][1]), sizes[j])
			{
				char			dest[32];
				char			exp[32];
				char			*src = strdup(pairs[i][1]);
				unsigned int	r;

				memset(dest, 'X', sizeof(dest));
				memset(exp, 'X', sizeof(exp));
				strcpy(dest, pairs[i][0]);
				strcpy(exp, pairs[i][0]);
				r = ref(exp, src, sizes[j]);
				CHECK_INT("return value", ft_strlcat(dest, src, sizes[j]), r);
				CHECK_MEM("dest (whole buffer; 'X' = untouched)", dest, exp, sizeof(dest));
				free(src);
			}
	CASE("size < strlen(dest): returns size + strlen(src), dest unchanged")
	{
		char	dest[16] = "Hello";

		CHECK_INT("return value", ft_strlcat(dest, "abc", 2), 5);
		CHECK_STR("dest", dest, "Hello");
	}
	return (mm_done());
}
