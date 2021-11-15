
#include "../fdf.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	slen;

	slen = len;
	while (len--)
		*(unsigned char *)b++ = (unsigned char)c;
	return (b - slen);
}
