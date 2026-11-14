// mm:files   ft_print_combn.c
// mm:allowed write
// mm:proto   void ft_print_combn(int n);
#include "mm.h"
#include "proto.h"

static char	g_exp[20000];
static int	g_k;

static void	gen(int n, int depth, int start, char *cur)
{
	int	d;

	if (depth == n)
	{
		if (g_k > 0)
			g_k += sprintf(g_exp + g_k, ", ");
		g_k += sprintf(g_exp + g_k, "%.*s", n, cur);
		return ;
	}
	for (d = start; d <= 9; d++)
	{
		cur[depth] = (char)('0' + d);
		gen(n, depth + 1, d + 1, cur);
	}
}

int	main(void)
{
	char	cur[10];
	int		n;

	for (n = 1; n <= 9; n++)
	{
		g_k = 0;
		g_exp[0] = '\0';
		gen(n, 0, 0, cur);
		CASE("ft_print_combn(%d)", n)
		{
			ft_print_combn(n);
			CHECK_OUTPUT(g_exp);
		}
	}
	CASE("ft_print_combn(2) twice in a row (no hidden state)")
	{
		char	twice[1000];

		g_k = 0;
		gen(2, 0, 0, cur);
		snprintf(twice, sizeof(twice), "%s%s", g_exp, g_exp);
		ft_print_combn(2);
		ft_print_combn(2);
		CHECK_OUTPUT(twice);
	}
	return (mm_done());
}
