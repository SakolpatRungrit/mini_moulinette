// mm:files   ft_ultimate_range.c
// mm:allowed malloc
// mm:proto   int ft_ultimate_range(int **range, int min, int max);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	int	t[][2] = {
		{0, 5}, {-3, 3}, {0, 1}, {-1, 0}, {10, 15}, {INT_MIN, INT_MIN + 5},
		{INT_MAX - 5, INT_MAX}, {0, 10000},
	};
	int	bad[][2] = {{5, 5}, {0, 0}, {10, 0}, {INT_MAX, INT_MIN}};
	int	i;

	for (i = 0; i < (int)(sizeof(t) / sizeof(*t)); i++)
		CASE("ft_ultimate_range(&range, %d, %d)", t[i][0], t[i][1])
		{
			int		*r = NULL;
			int		size = ft_ultimate_range(&r, t[i][0], t[i][1]);
			long	n = (long)t[i][1] - t[i][0];
			long	j;

			CHECK_INT("return value (the size)", size, n);
			CHECK(r != NULL, "*range is NULL");
			for (j = 0; r && j < n; j++)
				if (r[j] != t[i][0] + j)
				{
					mm_fail("range[%ld]: expected %ld, got %d", j, t[i][0] + j, r[j]);
					break ;
				}
			free(r);
		}
	for (i = 0; i < (int)(sizeof(bad) / sizeof(*bad)); i++)
		CASE("ft_ultimate_range(&range, %d, %d)  -- min >= max: returns 0, *range = NULL",
			bad[i][0], bad[i][1])
		{
			int	dummy;
			int	*r = &dummy;

			CHECK_INT("return value", ft_ultimate_range(&r, bad[i][0], bad[i][1]), 0);
			CHECK(r == NULL, "*range should be set to NULL");
		}
	return (mm_done());
}
