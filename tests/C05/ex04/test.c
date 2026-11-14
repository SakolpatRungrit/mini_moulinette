// mm:files   ft_fibonacci.c
// mm:allowed
// mm:proto   int ft_fibonacci(int index);
#include "mm.h"
#include "proto.h"

int	main(void)
{
	int	fib[33];
	int	idx[] = {0, 1, 2, 3, 4, 5, 6, 10, 15, 20, 25, 30, 32};
	int	i;

	fib[0] = 0;
	fib[1] = 1;
	for (i = 2; i < 33; i++)
		fib[i] = fib[i - 1] + fib[i - 2];
	for (i = 0; i < (int)(sizeof(idx) / sizeof(*idx)); i++)
		CASE("ft_fibonacci(%d)", idx[i])
			CHECK_INT("return value", ft_fibonacci(idx[i]), fib[idx[i]]);
	CASE("ft_fibonacci(-1) returns -1")
		CHECK_INT("return value", ft_fibonacci(-1), -1);
	CASE("ft_fibonacci(-42) returns -1")
		CHECK_INT("return value", ft_fibonacci(-42), -1);
	CASE("ft_fibonacci(INT_MIN) returns -1")
		CHECK_INT("return value", ft_fibonacci(INT_MIN), -1);
	return (mm_done());
}
