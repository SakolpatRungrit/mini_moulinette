// mm:files   ft_putstr.c
// mm:allowed write
// mm:proto   void ft_putstr(char *str);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	char	*s[] = {"Hello", "", "a", "Hello World!", "with\nnewline\n", "\ttabs\tand  spaces ",
		"42", "\x01\x7f control chars", "caf\xc3\xa9 (UTF-8)"};
	int		i;

	for (i = 0; i < (int)(sizeof(s) / sizeof(*s)); i++)
		CASE("ft_putstr(%s)", mm_show(s[i]))
		{
			char	*copy = strdup(s[i]);

			ft_putstr(copy);
			CHECK_OUTPUT(s[i]);
			CHECK_STR("the string itself (must not be modified)", copy, s[i]);
			free(copy);
		}
	CASE("a 10000-character string")
	{
		char	*big = malloc(10001);

		memset(big, 'x', 10000);
		big[10000] = '\0';
		big[5000] = 'Y';
		ft_putstr(big);
		CHECK_OUTPUT(big);
		free(big);
	}
	CASE("stops at the first '\\0': ft_putstr(\"abc\\0def\")")
	{
		ft_putstr("abc\0def");
		CHECK_OUTPUT("abc");
	}
	return (mm_done());
}
