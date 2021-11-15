
#include "../fdf.h"

char	*ft_strdup(const char *s1)
{
	char	*ret;
	size_t	len;

	len = ft_strlen(s1);
	ret = malloc(sizeof(char) * len + 1);
	if (!ret)
		return (NULL);
	ft_memcpy(ret, s1, len);
	ret[len] = 0;
	return (ret);
}
