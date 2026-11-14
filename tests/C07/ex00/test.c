// mm:files   ft_strdup.c
// mm:allowed malloc
// mm:proto   char *ft_strdup(char *src);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	char	*t[] = {"Hello", "", "a", "Hello World!", "with\nnewline", "caf\xc3\xa9 \x80\xff",
		"abc\0hidden"};
	int		i;

	for (i = 0; i < (int)(sizeof(t) / sizeof(*t)); i++)
		CASE("ft_strdup(%s)", mm_show(t[i]))
		{
			char	*src = strdup(t[i]);
			char	*r = ft_strdup(src);

			CHECK(r != NULL, "returned NULL");
			if (r)
			{
				CHECK_STR("copy", r, t[i]);
				CHECK(r != src, "returned src itself, not a new copy");
				r[0] = 'Z';
				CHECK_STR("src after changing the copy", src, t[i]);
				free(r);
			}
			free(src);
		}
	CASE("a 100000-character string")
	{
		char	*big = malloc(100001);
		char	*r;

		memset(big, 'q', 100000);
		big[100000] = '\0';
		r = ft_strdup(big);
		CHECK(r && strcmp(r, big) == 0, "copy differs from the original");
		free(r);
		free(big);
	}
	return (mm_done());
}
