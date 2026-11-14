// mm:files   ft_abs.h
// mm:type    header
#include "ft_abs.h"
#include "ft_abs.h"
#include "mm.h"

int	main(void)
{
	const int	v[] = {-5, 5, 0, -1, 1, INT_MAX, -INT_MAX, -42};
	int			i;

	for (i = 0; i < (int)(sizeof(v) / sizeof(*v)); i++)
		CASE("ABS(%d)", v[i])
			CHECK_INT("ABS", ABS(v[i]), v[i] < 0 ? -v[i] : v[i]);
	CASE("ABS(-42) with a literal")
		CHECK_INT("ABS", ABS(-42), 42);
	SOFT("ABS(2 - 5) == 3  -- put parentheses around the macro argument")
		CHECK_INT("ABS(2 - 5)", ABS(2 - 5), 3);
	SOFT("ABS(-3) * 2 == 6  -- put parentheses around the whole macro")
		CHECK_INT("ABS(-3) * 2", ABS(-3) * 2, 6);
	return (mm_done());
}
