// mm:files   ft_strstr.c
// mm:allowed
// mm:proto   char *ft_strstr(char *str, char *to_find);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	char	*t[][2] = {
		{"Hello World", "World"}, {"Hello World", "Hello"}, {"Hello World", "o"},
		{"Hello World", "xyz"}, {"Hello", ""}, {"", ""}, {"", "a"}, {"aaab", "aab"},
		{"abababc", "ababc"}, {"abc", "abcd"}, {"hello", "hello"}, {"hello", "o"},
		{"abcabc", "cab"}, {"needle in a haystack", "hay"}, {"mississippi", "issip"},
		{"aaa", "aaaa"}, {"case", "CASE"},
	};
	int		i;

	for (i = 0; i < (int)(sizeof(t) / sizeof(*t)); i++)
		CASE("ft_strstr(%s, %s)", mm_show(t[i][0]), mm_show(t[i][1]))
		{
			char	*str = strdup(t[i][0]);
			char	*find = strdup(t[i][1]);

			CHECK_PTR("return value", ft_strstr(str, find), strstr(str, find), str);
			free(str);
			free(find);
		}
	return (mm_done());
}
