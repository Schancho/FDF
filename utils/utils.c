
#include "../fdf.h"

int	ft_abs(int a)
{
	if (a < 0)
		return (-a);
	return (a);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

char	*ft_strchr(const char *s, int c)
{
	while (*(char *)s != '\0' && *s != (char)c)
		s++;
	if (*(char *)s == (char)c)
		return ((char *)s);
	return (0);
}
