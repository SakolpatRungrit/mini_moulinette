// mm:files   ft_strcapitalize.c
// mm:allowed
// mm:proto   char *ft_strcapitalize(char *str);
#include "mm.h"
#include "proto.h"

static int	is_alnum(char c)
{
	return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9'));
}

/* a word = run of letters/digits; first char upper, the rest lower */
static void	ref(char *s)
{
	int	i;

	for (i = 0; s[i]; i++)
	{
		if (i > 0 && is_alnum(s[i - 1]))
		{
			if (s[i] >= 'A' && s[i] <= 'Z')
				s[i] += 32;
		}
		else if (s[i] >= 'a' && s[i] <= 'z')
			s[i] -= 32;
	}
}

static void	test(int soft, const char *src)
{
	char	*s = strdup(src);
	char	*exp = strdup(src);

	ref(exp);
	if (soft)
	{
		SOFT("ft_strcapitalize(%s)  -- bytes > 127 separate words", mm_show(src))
			CHECK_STR("result", ft_strcapitalize(s), exp);
	}
	else
	{
		CASE("ft_strcapitalize(%s)", mm_show(src))
		{
			char	*ret = ft_strcapitalize(s);

			CHECK_STR("result", s, exp);
			CHECK(ret == s, "should return str");
		}
	}
	free(s);
	free(exp);
}

int	main(void)
{
	char	all[128];
	int		i;

	test(0, "salut, comment tu vas ? 42mots quarante-deux; cinquante+et+un");
	test(0, "");
	test(0, "a");
	test(0, "A");
	test(0, "hello");
	test(0, "HELLO WORLD");
	test(0, "hELLO wORLD");
	test(0, "42MOTS 42mots");
	test(0, "   leading and trailing   ");
	test(0, "a.b,c;d:e!f?g");
	test(0, "x-Y_z");
	test(0, "multiple   spaces\tand\ttabs\nnewlines");
	test(0, "1st 2ND 3rD");
	test(0, "@aBC [aBC `aBC {aBC");
	for (i = 0; i < 127; i++)
		all[i] = (char)(127 - i);
	all[127] = '\0';
	test(0, all);
	test(1, "caf\xc3\xa9 \xc3\xa9t\xc3\xa9 \x80hello");
	return (mm_done());
}
