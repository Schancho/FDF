#include "fdf.h"

int     get_height(char *file_name)
{
    int fd;
    char *line;
    int height;

    height = 0;
    fd = open(file_name, O_RDONLY, 0777);
    while (get_next_line(fd, &line) > 0)
    {
        height++;
        free(line);
    }
    if (line)
    {
        free(line);
    }
    close(fd);
    return (height);
}

int     get_width(char *file_name)
{
    int fd;
    char *line;
    int width;

    width = 0;
    fd = open(file_name, O_RDONLY, 0777);
    get_next_line(fd, &line);

    if (line)
    {
        width = ft_wdcounter(line, ' ');
        free(line);
    }
    close(fd);
    return (width);
}

t_fdf   parser(char *file_name)
{
    t_fdf fdf;
    int i;
    int fd;
    char *line;

    fd = open(file_name, O_RDONLY, 0777);
    fdf.height = get_height(file_name);
    fdf.width = get_width(file_name);
    fdf.matrix = malloc(sizeof(char **) * (fdf.height + 1));
    i = 0;
    while (i < fdf.height)
    {
        get_next_line(fd, &line);
        fdf.matrix[i++] = ft_split(line, ' ');
    }
    fdf.matrix[i] = NULL;
    return (fdf);
}

void	isometric(float *x, float *y, float z)
{
	*x = (*x - *y) * cos(0.8);
	*y = (*x + *y) * sin(0.8) - z;
}

void    draw_line(float x, float y, float x1, float y1, t_fdf fdf)
{
    int max;
    float x_step;
    float y_step;
    int z;
    int z1;
    char *color1;
    char *color2;

    z = ft_atoi(fdf.matrix[(int)y][(int)x]);
    z1 = ft_atoi(fdf.matrix[(int)y1][(int)x1]);
    fdf.color = 0xffffff;
    color1 = strchr(fdf.matrix[(int)y][(int)x], ',') ;
    color2 = strchr(fdf.matrix[(int)y1][(int)x1], ',');
    if (color1)
        fdf.color = ft_atoi_base(color1 + 1, 16);
    if (color2)
        fdf.color = ft_atoi_base(color2 + 1, 16);  
    x *= SCALE;
    y *= SCALE;
    x1 *= SCALE;
    y1 *= SCALE;

    //printf("before %f %f %f %f\n",x, x1, y, y1);
    isometric(&x, &y, z);
    isometric(&x1, &y1 , z1);
    //printf("after %f %f %f %f\n",x, x1, y, y1);
    x_step = x1 - x;
    y_step = y1 - y;
    max = ft_max(ft_abs(x_step), ft_abs(y_step));

    x_step /= max;
    y_step /= max;
    //printf("xstep %d ystep %d", x_step, y_step);
    //exit(0);
    while ((int)(x - x1) || (int)(y - y1))
    {
        //printf ("check\n");
        mlx_pixel_put(fdf.mlx, fdf.win, x + 400, y + 200 , fdf.color);
        x += x_step;
        y += y_step;
    }
}

void    draw(t_fdf fdf)
{
    int y;
    int x;


    printf("%d %d\n", fdf.height, fdf.width);
    y = 0;
    x = 0;
    while (y < fdf.height)
    {
        x = 0;
        while (x < fdf.width)
        {
            if (x < fdf.width - 1)
                draw_line(x,y,x+1,y, fdf);
            if (y < fdf.height - 1)
                
                draw_line(x,y,x,y+1, fdf);
            x++;
        }
        y++;
    }    
}

int main(int ac, char **av)
{
    t_fdf fdf;

    (void)ac;
    (void)av;
    fdf = parser(av[1]);
    fdf.mlx = mlx_init();
    fdf.win = mlx_new_window(fdf.mlx, 4000, 4000, "FDF");
    draw(fdf);
    mlx_loop(fdf.mlx);

    return(0);
}