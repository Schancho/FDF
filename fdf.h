#ifndef FDF_H
#define FDF_H
#include "mlx.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define SCALE 20

typedef struct s_fdf
{    
    void    *mlx;
    void    *win;
    char ***matrix;
    int width;
    int height;

    int color;
    
}               t_fdf;



int		get_next_line(int fd, char **line);
int		ft_wdcounter(char const *str, char c);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
int		ft_atoi(const char *str);
int     ft_atoi_base(const char *str, int str_base);
void	ft_bzero(void *s, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memset(void *b, int c, size_t len);
int		ft_max(int a, int b);
int		ft_abs(int a);

#endif