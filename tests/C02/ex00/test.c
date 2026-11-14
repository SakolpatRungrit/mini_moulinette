// mm:files   ft_strcpy.c
// mm:allowed
// mm:proto   char *ft_strcpy(char *dest, char *src);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	char	*s[] = {"Hello", "", "a", "Hello World!", "with\nnewline", "caf\xc3\xa9 \x80\xff"};
	int		i;

	for (i = 0; i < (int)(sizeof(s) / sizeof(*s)); i++)
		CASE("ft_strcpy(dest, %s)", mm_show(s[i]))
		{
			char	dest[32];
			char	exp[32];
			char	*src = strdup(s[i]);
			char	*ret;

			memset(dest, 'X', sizeof(dest));
			memset(exp, 'X', sizeof(exp));
			strcpy(exp, s[i]);
			ret = ft_strcpy(dest, src);
			CHECK_MEM("dest (whole buffer; 'X' = untouched)", dest, exp, sizeof(dest));
			CHECK(ret == dest, "should return dest");
			CHECK_STR("src (must not change)", src, s[i]);
			free(src);
		}
	CASE("copies the '\\0' too: dest = \"XXXXXXX\", src = \"abc\"")
	{
		char	dest[8] = "XXXXXXX";

		ft_strcpy(dest, "abc");
		CHECK_MEM("dest", dest, "abc\0XXX", 8);
	}
	CASE("dest buffer exactly the right size (malloc(strlen(src) + 1))")
	{
		char	*src = "exact size";
		char	*dest = malloc(strlen(src) + 1);

		ft_strcpy(dest, src);
		CHECK_STR("dest", dest, src);
		free(dest);
	}
	return (mm_done());
}
