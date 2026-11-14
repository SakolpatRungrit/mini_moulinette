// mm:files   ft_putstr_non_printable.c
// mm:allowed write
// mm:proto   void ft_putstr_non_printable(char *str);
#include "mm.h"
#include "proto.h"

static void	ref(const char *s, char *out)
{
	const unsigned char	*u = (const unsigned char *)s;

	*out = '\0';
	for (; *u; u++)
	{
		if (*u >= 32 && *u <= 126)
			out += sprintf(out, "%c", *u);
		else
			out += sprintf(out, "\\%02x", *u);
	}
}

static void	test(int soft, const char *src)
{
	char	exp[4096];
	char	*s = strdup(src);

	ref(src, exp);
	if (soft)
	{
		SOFT("ft_putstr_non_printable(%s)  -- bytes > 127 must print as \\80..\\ff", mm_show(src))
		{
			ft_putstr_non_printable(s);
			CHECK_OUTPUT(exp);
		}
	}
	else
	{
		CASE("ft_putstr_non_printable(%s)", mm_show(src))
		{
			ft_putstr_non_printable(s);
			CHECK_OUTPUT(exp);
		}
	}
	free(s);
}

int	main(void)
{
	char	ctrl[33];
	int		i;

	test(0, "Coucou\ntu vas bien ?");
	test(0, "");
	test(0, "Hello World!");
	test(0, "\x01");
	test(0, "\x1f");
	test(0, "\x7f");
	test(0, "\t\n\v\f\r");
	test(0, "~ and space are printable");
	test(0, "\x0a\x0b\x0c\x0d\x0e\x0f -> lowercase hex");
	for (i = 0; i < 31; i++)
		ctrl[i] = (char)(i + 1);
	ctrl[31] = 127;
	ctrl[32] = '\0';
	test(0, ctrl);
	test(1, "\x80");
	test(1, "\xff");
	test(1, "caf\xc3\xa9");
	return (mm_done());
}
