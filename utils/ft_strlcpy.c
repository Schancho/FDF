
#include "../fdf.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;

	len = ft_strlen(src);
	if (size > 0)
	{
		while (--size && *src != 0)
		{
			ft_memset(dst, *(char *)src, 1);
			dst++;
			src++;
		}
		*dst = 0;
	}
	return (len);
}
