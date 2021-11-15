
#include "../fdf.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	sn;

	sn = n;
	if (!dst && !src)
		return (NULL);
	if (src == dst)
		return (dst);
	while (n--)
		*(unsigned char *)dst++ = *(unsigned char *)src++;
	return (dst - sn);
}
