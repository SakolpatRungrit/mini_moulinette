// mm:files   ft_ten_queens_puzzle.c
// mm:allowed write
// mm:proto   int ft_ten_queens_puzzle(void);
#include "mm.h"
#include "proto.h"

static char	g_out[8000];
static int	g_k;
static int	g_count;

static void	solve(int *pos, int col)
{
	int	row;
	int	c;
	int	ok;

	if (col == 10)
	{
		for (c = 0; c < 10; c++)
			g_out[g_k++] = (char)('0' + pos[c]);
		g_out[g_k++] = '\n';
		g_count++;
		return ;
	}
	for (row = 0; row < 10; row++)
	{
		ok = 1;
		for (c = 0; c < col && ok; c++)
			if (pos[c] == row || abs(pos[c] - row) == col - c)
				ok = 0;
		if (ok)
		{
			pos[col] = row;
			solve(pos, col + 1);
		}
	}
}

int	main(void)
{
	int	pos[10];

	solve(pos, 0);
	g_out[g_k] = '\0';
	TIMEOUT(10);
	CASE("ft_ten_queens_puzzle() returns 724")
	{
		int	r = ft_ten_queens_puzzle();

		mm_take_output(NULL);
		CHECK_INT("return value", r, g_count);
	}
	TIMEOUT(10);
	CASE("prints all 724 solutions, one per line, in order (first: 0257948136)")
	{
		ft_ten_queens_puzzle();
		CHECK_OUTPUT(g_out);
	}
	return (mm_done());
}
