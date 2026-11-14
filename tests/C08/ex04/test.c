// mm:files   ft_strs_to_tab.c
// mm:allowed malloc
#include "ft_stock_str.h"
#include "mm.h"

struct s_stock_str	*ft_strs_to_tab(int ac, char **av);

static void	test(int ac, char **src)
{
	char	desc[512];
	int		k;
	int		i;

	k = sprintf(desc, "ft_strs_to_tab(%d, {", ac);
	for (i = 0; i < ac && i < 5; i++)
		k += sprintf(desc + k, "%s%s", i ? ", " : "", mm_show(src[i]));
	sprintf(desc + k, "%s})", ac > 5 ? ", ..." : "");
	CASE("%s", desc)
	{
		char		**av = malloc(sizeof(char *) * (ac + 1));
		t_stock_str	*tab;

		for (i = 0; i < ac; i++)
			av[i] = strdup(src[i]);
		av[ac] = NULL;
		tab = ft_strs_to_tab(ac, av);
		CHECK(tab != NULL, "returned NULL");
		for (i = 0; tab && i < ac; i++)
		{
			CHECK_INT("size", tab[i].size, (int)strlen(src[i]));
			CHECK_STR("str", tab[i].str, src[i]);
			CHECK_STR("copy", tab[i].copy, src[i]);
			CHECK(tab[i].copy != av[i], "tab[%d].copy is av[%d] itself, it must be a new copy", i, i);
			if (tab[i].copy && tab[i].copy != av[i] && av[i][0])
			{
				av[i][0] = '#';
				CHECK(tab[i].copy[0] != '#', "tab[%d].copy changed when av[%d] changed", i, i);
			}
		}
		if (tab)
			CHECK(tab[ac].str == 0, "the last element must have str == 0 (got %s)", mm_show(tab[ac].str));
	}
}

int	main(void)
{
	char	*big[50];
	char	names[50][8];
	int		i;

	test(3, (char *[]){"hello", "", "world"});
	test(1, (char *[]){"solo"});
	test(0, (char *[]){NULL});
	test(4, (char *[]){"./a.out", "with space", "\ttab", "42"});
	for (i = 0; i < 50; i++)
	{
		sprintf(names[i], "s%d", i * 7);
		big[i] = names[i];
	}
	test(50, big);
	return (mm_done());
}
