// mm:files   ft_strcat.c
// mm:allowed
// mm:proto   char *ft_strcat(char *dest, char *src);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	char	*t[][2] = {
		{"Hello", " World"}, {"", "abc"}, {"abc", ""}, {"", ""}, {"a", "b"},
		{"42 ", "Bangkok"}, {"line\n", "next\n"},
	};
	int		i;

	for (i = 0; i < (int)(sizeof(t) / sizeof(*t)); i++)
		CASE("dest = %s; ft_strcat(dest, %s)", mm_show(t[i][0]), mm_show(t[i][1]))
		{
			char	dest[32];
			char	exp[32];
			char	*src = strdup(t[i][1]);
			char	*ret;

			memset(dest, 'X', sizeof(dest));
			memset(exp, 'X', sizeof(exp));
			strcpy(dest, t[i][0]);
			strcpy(exp, t[i][0]);
			strcat(exp, t[i][1]);
			ret = ft_strcat(dest, src);
			CHECK_MEM("dest (whole buffer; 'X' = untouched)", dest, exp, sizeof(dest));
			CHECK(ret == dest, "should return dest");
			free(src);
		}
	CASE("chained: ft_strcat(ft_strcat(dest, \"ab\"), \"cd\")")
	{
		char	dest[16] = "";

		ft_strcat(ft_strcat(dest, "ab"), "cd");
		CHECK_STR("dest", dest, "abcd");
	}
	CASE("dest buffer exactly big enough (malloc)")
	{
		char	*dest = malloc(12);

		strcpy(dest, "Hello");
		ft_strcat(dest, " World");
		CHECK_STR("dest", dest, "Hello World");
		free(dest);
	}
	return (mm_done());
}
