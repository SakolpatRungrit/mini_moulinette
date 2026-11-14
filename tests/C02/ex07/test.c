// mm:files   ft_strupcase.c
// mm:allowed
// mm:proto   char *ft_strupcase(char *str);
#include "mm.h"
#include "proto.h"

static void	ref(char *s)
{
	for (; *s; s++)
		if (*s >= 'a' && *s <= 'z')
			*s -= 32;
}

int	main(void)
{
	char	*t[] = {"hello", "", "Hello World!", "ALREADY UP", "mIxEd CaSe 42",
		"`az{", "@AZ[", "a", "z", "caf\xc3\xa9 \x80\xff"};
	char	all[256];
	int		i;

	for (i = 0; i < 255; i++)
		all[i] = (char)(i + 1);
	all[255] = '\0';
	for (i = 0; i <= (int)(sizeof(t) / sizeof(*t)); i++)
	{
		char	*src = i < (int)(sizeof(t) / sizeof(*t)) ? t[i] : all;

		CASE("ft_strupcase(%s)", i < (int)(sizeof(t) / sizeof(*t)) ? mm_show(src)
			: "every byte from 1 to 255")
		{
			char	*s = strdup(src);
			char	*exp = strdup(src);
			char	*ret;

			ref(exp);
			ret = ft_strupcase(s);
			CHECK_MEM("result", s, exp, strlen(src) + 1);
			CHECK(ret == s, "should return str");
			free(s);
			free(exp);
		}
	}
	return (mm_done());
}
