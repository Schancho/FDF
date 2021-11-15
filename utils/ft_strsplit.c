
#include "../fdf.h"

static char	**memory_giver(char const *str, char c)
{
	char	**res;
	int		letters;
	int		i;
	int		j;

	res = (char **)malloc(sizeof(char *) * (ft_wdcounter(str, c) + 1));
	i = 0;
	j = 0;
	while (str[i])
	{
		letters = 0;
		while (str[i] == c && str[i])
			i++;
		while (str[i] != c && str[i] != '\0')
		{
			letters++;
			i++;
		}
		if (letters > 0)
			res[j++] = (char *)malloc(sizeof(char) * letters + 1);
	}
	res[j] = 0;
	return (res);
}

char	**ft_split(char const *str, char c)
{
	char	**res;
	int		i;
	int		j;
	int		str_number;
	int		size;

	if (str == NULL)
		return (NULL);
	size = ft_wdcounter(str, c);
	res = memory_giver(str, c);
	if (res == NULL)
		return (NULL);
	i = 0;
	str_number = 0;
	while (str_number < size)
	{
		while (str[i] == c && str[i])
			i++;
		j = 0;
		while (str[i] != c && str[i])
			res[str_number][j++] = str[i++];
		res[str_number][j] = '\0';
		str_number++;
	}
	return (res);
}
