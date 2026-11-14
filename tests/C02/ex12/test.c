// mm:files   ft_print_memory.c
// mm:allowed write
// mm:proto   void *ft_print_memory(void *addr, unsigned int size);
#include "mm.h"
#include "proto.h"
#include <stdint.h>

/* reference output: "<16-hex addr>: <hex in groups of 2 bytes> <chars>\n" */
static char	*ref(const void *addr, unsigned int size)
{
	const unsigned char	*p = addr;
	char				*out = malloc(size / 16 * 80 + 160);
	int					k = 0;
	unsigned int		off;
	unsigned int		i;

	out[0] = '\0';
	for (off = 0; off < size; off += 16)
	{
		k += sprintf(out + k, "%016lx: ", (unsigned long)(uintptr_t)(p + off));
		for (i = 0; i < 16; i++)
		{
			if (off + i < size)
				k += sprintf(out + k, "%02x", p[off + i]);
			else
				k += sprintf(out + k, "  ");
			if (i % 2 == 1)
				k += sprintf(out + k, " ");
		}
		for (i = 0; i < 16 && off + i < size; i++)
			out[k++] = (p[off + i] >= 32 && p[off + i] <= 126) ? (char)p[off + i] : '.';
		out[k++] = '\n';
		out[k] = '\0';
	}
	return (out);
}

static void	test(int soft, const char *what, const void *data, unsigned int size)
{
	unsigned char	*buf = malloc(size ? size : 1);
	char			*exp;

	memcpy(buf, data, size);
	exp = ref(buf, size);
	if (soft)
	{
		SOFT("%s (size %u)", what, size)
		{
			ft_print_memory(buf, size);
			CHECK_OUTPUT(exp);
		}
	}
	else
	{
		CASE("%s (size %u)", what, size)
		{
			void	*ret = ft_print_memory(buf, size);

			CHECK_OUTPUT(exp);
			CHECK(ret == buf, "should return addr");
		}
	}
	free(exp);
	free(buf);
}

int	main(void)
{
	const char		subject[] = "Bonjour les aminches\t\n\tc  est fou\ttout\tce qu on "
		"peut faire avec\t\n\tprint_memory\n\n\n\tlol.lol\n ";
	unsigned char	bytes[256];
	int				i;

	for (i = 0; i < 256; i++)
		bytes[i] = (unsigned char)i;
	test(0, "the subject's example", subject, sizeof(subject));
	test(0, "exactly one line", "0123456789abcdef", 16);
	test(0, "one line + 1 byte", "0123456789abcdefX", 17);
	test(0, "15 bytes (padding before the text)", "0123456789abcde", 15);
	test(0, "1 byte", "A", 1);
	test(0, "an odd size inside a 2-byte group", "Hello", 5);
	test(0, "non-printable bytes 0..31 and 127 shown as '.'", bytes, 32);
	test(0, "bytes 32..127", bytes + 32, 96);
	CASE("size 0: prints nothing and returns addr")
	{
		char	c = 'x';

		CHECK(ft_print_memory(&c, 0) == &c, "should return addr");
		CHECK_OUTPUT("");
	}
	test(1, "bytes 128..255 in lowercase 2-digit hex (unsigned char!)", bytes + 128, 128);
	return (mm_done());
}
