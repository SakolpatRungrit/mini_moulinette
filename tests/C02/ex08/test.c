// mm:files   ft_strlowcase.c
// mm:allowed
// mm:proto   char *ft_strlowcase(char *str);
#include "mm.h"
#include "proto.h"

static void	ref(char *s)
{
	for (; *s; s++)
		if (*s >= 'A' && *s <= 'Z')
			*s += 32;
}

int	main(void)
{
	char	*t[] = {"HELLO", "", "Hello World!", "already low", "mIxEd CaSe 42",
		"@AZ[", "`az{", "A", "Z", "CAF\xc3\x89 \x80\xff"};
	char	all[256];
	int		i;
	int		n = (int)(sizeof(t) / sizeof(*t));

	for (i = 0; i < 255; i++)
		all[i] = (char)(i + 1);
	all[255] = '\0';
	for (i = 0; i <= n; i++)
	{
		char	*src = i < n ? t[i] : all;

		CASE("ft_strlowcase(%s)", i < n ? mm_show(src) : "every byte from 1 to 255")
		{
			char	*s = strdup(src);
			char	*exp = strdup(src);
			char	*ret;

			ref(exp);
			ret = ft_strlowcase(s);
			CHECK_MEM("result", s, exp, strlen(src) + 1);
			CHECK(ret == s, "should return str");
			free(s);
			free(exp);
		}
	}
	return (mm_done());
}
