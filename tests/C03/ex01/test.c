// mm:files   ft_strncmp.c
// mm:allowed
// mm:proto   int ft_strncmp(char *s1, char *s2, unsigned int n);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	struct { char *a; char *b; unsigned int n; } t[] = {
		{"abc", "abc", 3}, {"abc", "abd", 2}, {"abc", "abd", 3}, {"abd", "abc", 3},
		{"abc", "abd", 0}, {"", "", 0}, {"", "", 5}, {"", "a", 1}, {"a", "", 1},
		{"abc", "abc", 100}, {"abc", "abcd", 3}, {"abc", "abcd", 4}, {"abcd", "abc", 4},
		{"Hello", "HELLO", 1}, {"Hello", "HELLO", 2}, {"same\0x", "same\0y", 7},
		{"x", "y", 0}, {"test", "tesT", 4},
	};
	int	i;
	int	n = (int)(sizeof(t) / sizeof(*t));

	for (i = 0; i < n; i++)
		CASE("ft_strncmp(%s, %s, %u)", mm_show(t[i].a), mm_show(t[i].b), t[i].n)
		{
			char	*a = strdup(t[i].a);
			char	*b = strdup(t[i].b);

			CHECK_SIGN("return value", ft_strncmp(a, b, t[i].n), strncmp(t[i].a, t[i].b, t[i].n));
			free(a);
			free(b);
		}
	SOFT("ft_strncmp(\"\\x80\", \"a\", 1) > 0  -- compare as unsigned char")
		CHECK_SIGN("return value", ft_strncmp("\x80", "a", 1), 1);
	SOFT("ft_strncmp(\"abc\", \"abd\", UINT_MAX) < 0  -- no overflow on huge n")
		CHECK_SIGN("return value", ft_strncmp("abc", "abd", UINT_MAX), -1);
	return (mm_done());
}
