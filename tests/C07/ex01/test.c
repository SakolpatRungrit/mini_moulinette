// mm:files   ft_range.c
// mm:allowed malloc
// mm:proto   int *ft_range(int min, int max);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	int	t[][2] = {
		{0, 5}, {-3, 3}, {0, 1}, {-1, 0}, {10, 15}, {-10, -5},
		{INT_MIN, INT_MIN + 5}, {INT_MAX - 5, INT_MAX}, {0, 10000},
	};
	int	bad[][2] = {{5, 5}, {0, 0}, {10, 0}, {-5, -10}, {INT_MAX, INT_MIN}};
	int	i;

	for (i = 0; i < (int)(sizeof(t) / sizeof(*t)); i++)
		CASE("ft_range(%d, %d)", t[i][0], t[i][1])
		{
			int		*r = ft_range(t[i][0], t[i][1]);
			long	n = (long)t[i][1] - t[i][0];
			long	j;

			CHECK(r != NULL, "returned NULL");
			for (j = 0; r && j < n; j++)
				if (r[j] != t[i][0] + j)
				{
					mm_fail("tab[%ld]: expected %ld, got %d", j, t[i][0] + j, r[j]);
					break ;
				}
			free(r);
		}
	for (i = 0; i < (int)(sizeof(bad) / sizeof(*bad)); i++)
		CASE("ft_range(%d, %d)  -- min >= max: returns NULL", bad[i][0], bad[i][1])
			CHECK(ft_range(bad[i][0], bad[i][1]) == NULL, "should return NULL");
	return (mm_done());
}
