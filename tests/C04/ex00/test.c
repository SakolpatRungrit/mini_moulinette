// mm:files   ft_strlen.c
// mm:allowed
// mm:proto   int ft_strlen(char *str);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	char	*s[] = {"", "a", "Hello", "Hello World!", "  spaces  ", "\n\t", "caf\xc3\xa9",
		"\x80\xff high bytes"};
	int		i;

	for (i = 0; i < (int)(sizeof(s) / sizeof(*s)); i++)
		CASE("ft_strlen(%s)", mm_show(s[i]))
		{
			char	*copy = strdup(s[i]);

			CHECK_INT("return value", ft_strlen(copy), (int)strlen(s[i]));
			free(copy);
		}
	CASE("stops at the first '\\0': ft_strlen(\"abc\\0def\")")
	{
		CHECK_INT("return value", ft_strlen("abc\0def"), 3);
	}
	CASE("a 100000-character string")
	{
		char	*big = malloc(100001);

		memset(big, 'z', 100000);
		big[100000] = '\0';
		CHECK_INT("return value", ft_strlen(big), 100000);
		free(big);
	}
	return (mm_done());
}
