// mm:files   ft.h
// mm:type    header
#include "ft.h"
#include "ft.h"
#include "mm.h"

/* Calls every function BEFORE defining it: if a prototype is missing from
   ft.h, this does not compile. If a prototype is wrong, the definitions
   below conflict with it and this does not compile either. */
static void	use_all(void)
{
	int	a = 1;
	int	b = 2;

	ft_putchar('x');
	ft_swap(&a, &b);
	ft_putstr("x");
	(void)ft_strlen("x");
	(void)ft_strcmp("a", "b");
}

void	ft_putchar(char c)
{
	(void)c;
}

void	ft_swap(int *a, int *b)
{
	(void)a;
	(void)b;
}

void	ft_putstr(char *str)
{
	(void)str;
}

int	ft_strlen(char *str)
{
	(void)str;
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	(void)s1;
	(void)s2;
	return (0);
}

int	main(void)
{
	CASE("ft.h declares ft_putchar, ft_swap, ft_putstr, ft_strlen, ft_strcmp with the right prototypes")
		use_all();
	return (mm_done());
}
