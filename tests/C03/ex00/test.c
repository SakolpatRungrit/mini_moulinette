// mm:files   ft_strcmp.c
// mm:allowed
// mm:proto   int ft_strcmp(char *s1, char *s2);
#include "mm.h"
#include "proto.h"

static int	ref_diff(const char *a, const char *b)
{
	while (*a && *a == *b)
	{
		a++;
		b++;
	}
	return ((unsigned char)*a - (unsigned char)*b);
}

int	main(void)
{
	char	*t[][2] = {
		{"abc", "abc"}, {"", ""}, {"", "a"}, {"a", ""}, {"abc", "abd"}, {"abd", "abc"},
		{"abc", "abcd"}, {"abcd", "abc"}, {"ABC", "abc"}, {"abc", "ABC"}, {"Hello", "Hellp"},
		{"a", "b"}, {"z", "a"}, {"123", "124"}, {"same\0diff", "same\0else"}, {" ", "\t"},
	};
	int		i;
	int		n = (int)(sizeof(t) / sizeof(*t));

	for (i = 0; i < n; i++)
		CASE("ft_strcmp(%s, %s)", mm_show(t[i][0]), mm_show(t[i][1]))
		{
			char	*a = strdup(t[i][0]);
			char	*b = strdup(t[i][1]);

			CHECK_SIGN("return value", ft_strcmp(a, b), strcmp(t[i][0], t[i][1]));
			free(a);
			free(b);
		}
	for (i = 0; i < n; i++)
		SOFT("ft_strcmp(%s, %s) returns the exact difference %d", mm_show(t[i][0]),
			mm_show(t[i][1]), ref_diff(t[i][0], t[i][1]))
			CHECK_INT("return value", ft_strcmp(t[i][0], t[i][1]), ref_diff(t[i][0], t[i][1]));
	SOFT("ft_strcmp(\"\\x80\", \"a\") > 0  -- compare as unsigned char, like the real strcmp")
		CHECK_SIGN("return value", ft_strcmp("\x80", "a"), 1);
	return (mm_done());
}
