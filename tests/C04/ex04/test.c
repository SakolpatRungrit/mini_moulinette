// mm:files   ft_putnbr_base.c
// mm:allowed write
// mm:proto   void ft_putnbr_base(int nbr, char *base);
#include "mm.h"
#include "proto.h"

static int	valid(const char *b)
{
	int	i;
	int	j;

	for (i = 0; b[i]; i++)
	{
		if (b[i] == '+' || b[i] == '-')
			return (0);
		for (j = i + 1; b[j]; j++)
			if (b[i] == b[j])
				return (0);
	}
	return (i >= 2);
}

static void	ref(int nbr, const char *base, char *out)
{
	long	n = nbr;
	long	len = (long)strlen(base);
	char	tmp[64];
	int		k = 0;

	*out = '\0';
	if (!valid(base))
		return ;
	if (n < 0)
	{
		*out++ = '-';
		n = -n;
	}
	do
	{
		tmp[k++] = base[n % len];
		n /= len;
	} while (n > 0);
	while (k > 0)
		*out++ = tmp[--k];
	*out = '\0';
}

int	main(void)
{
	char	*dec = "0123456789";
	char	*hex = "0123456789ABCDEF";
	char	*lhex = "0123456789abcdef";
	char	*bin = "01";
	char	*pony = "poneyvif";
	struct { int n; char *base; } t[] = {
		{42, dec}, {-42, dec}, {0, dec}, {7, dec}, {INT_MAX, dec}, {INT_MIN, dec},
		{42, bin}, {0, bin}, {-1, bin}, {INT_MAX, bin}, {INT_MIN, bin},
		{255, hex}, {-255, hex}, {INT_MIN, hex}, {INT_MAX, lhex}, {3054, lhex},
		{40, pony}, {-40, pony}, {INT_MIN, pony}, {5, "ab"}, {123, "a1b2c3d4e5"},
		{100, "!@#$%^&*()"},
		{42, ""}, {42, "0"}, {42, "0120"}, {42, "01+"}, {42, "-01"}, {42, "+-"},
		{42, "aa"}, {INT_MIN, "0123456789A1"},
	};
	char	exp[64];
	int		i;

	for (i = 0; i < (int)(sizeof(t) / sizeof(*t)); i++)
	{
		ref(t[i].n, t[i].base, exp);
		CASE("ft_putnbr_base(%d, %s)%s", t[i].n, mm_show(t[i].base),
			valid(t[i].base) ? "" : "  -- invalid base: print nothing")
		{
			char	*b = strdup(t[i].base);

			ft_putnbr_base(t[i].n, b);
			CHECK_OUTPUT(exp);
			free(b);
		}
	}
	return (mm_done());
}
