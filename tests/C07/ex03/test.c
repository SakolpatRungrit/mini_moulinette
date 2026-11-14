// mm:files   ft_strjoin.c
// mm:allowed malloc
// mm:proto   char *ft_strjoin(int size, char **strs, char *sep);
#include "mm.h"
#include "proto.h"

static void	test(int size, char **strs, char *sep, const char *exp)
{
	char	desc[512];
	int		k;
	int		i;

	k = sprintf(desc, "ft_strjoin(%d, {", size);
	for (i = 0; i < size && i < 6; i++)
		k += sprintf(desc + k, "%s%s", i ? ", " : "", mm_show(strs[i]));
	sprintf(desc + k, "%s}, %s)", size > 6 ? ", ..." : "", mm_show(sep));
	CASE("%s", desc)
	{
		char	*r = ft_strjoin(size, strs, sep);

		CHECK_STR("result", r, exp);
		free(r);
	}
}

int	main(void)
{
	char	*a[] = {"Hello", "World", "42"};
	char	*b[] = {"solo"};
	char	*c[] = {"", "", ""};
	char	*d[] = {"a", "b"};
	char	*e[] = {"x", "", "y", ""};
	char	*f[] = {"multi", "char", "sep"};
	char	*big[100];
	char	exp[400];
	int		i;
	int		k = 0;

	test(3, a, ", ", "Hello, World, 42");
	test(1, b, "--", "solo");
	test(3, c, "-", "--");
	test(2, d, "", "ab");
	test(4, e, "/", "x//y/");
	test(3, f, " <=> ", "multi <=> char <=> sep");
	test(0, a, ", ", "");
	for (i = 0; i < 100; i++)
	{
		big[i] = "ab";
		k += sprintf(exp + k, "%sab", i ? "," : "");
	}
	test(100, big, ",", exp);
	CASE("size 0 returns an empty string you can free()")
	{
		char	*r = ft_strjoin(0, NULL, "sep");

		CHECK(r != NULL, "returned NULL, should be \"\" (malloc'd)");
		if (r)
		{
			CHECK_STR("result", r, "");
			free(r);
		}
	}
	return (mm_done());
}
