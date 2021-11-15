
#include "../fdf.h"

char	*ft_strjoin(char *s, char c)
{
	int		i;
	char	*str;

	i = 0;
	while (s[i])
		i++;
	str = (char *)malloc(i + 2);
	if (!str)
		return (0);
	i = 0;
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = '\0';
	return (str);
}

int	get_next_line(int fd, char **line)
{
	int		flag;
	char	buffer;
	char	*tmp;

	*line = (char *)malloc(1);
	if (!line)
		return (-1);
	*line[0] = '\0';
	flag = 1;
	while (flag > 0)
	{
		flag = read(fd, &buffer, 1);
		if (buffer == '\n')
			break ;
		tmp = ft_strjoin(*line, buffer);
		free(*line);
		*line = tmp;
	}
	return (flag);
}
