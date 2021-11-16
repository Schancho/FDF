/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schancho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 08:11:01 by schancho          #+#    #+#             */
/*   Updated: 2021/11/16 08:27:59 by schancho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	get_height(char *file_name)
{
	int		fd;
	char	*line;
	int		height;

	height = 0;
	fd = open(file_name, O_RDONLY, 0777);
	while (get_next_line(fd, &line) > 0)
	{
		height++;
		free (line);
	}
	if (line)
		free (line);
	close (fd);
	return (height);
}

int	get_width(char *file_name)
{
	int		fd;
	char	*line;
	int		width;

	width = 0;
	fd = open(file_name, O_RDONLY, 0777);
	get_next_line(fd, &line);
	if (line)
	{
		width = ft_wdcounter(line, ' ');
		free (line);
	}
	close (fd);
	return (width);
}

t_fdf	parser(char *file_name)
{
	t_fdf	fdf;
	int		i;
	int		fd;
	char	*line;

	fdf.shift_x = 0;
	fdf.shift_y = 0;
	fd = open(file_name, O_RDONLY, 0777);
	if (fd == -1)
	{
		perror("Error: ");
		exit (1);
	}
	fdf.height = get_height(file_name);
	fdf.width = get_width(file_name);
	fdf.matrix = malloc(sizeof(char **) * (fdf.height + 1));
	i = 0;
	while (i < fdf.height)
	{
		get_next_line(fd, &line);
		fdf.matrix[i++] = ft_split(line, ' ');
		free (line);
	}
	fdf.matrix[i] = NULL;
	return (fdf);
}

void	isometric(float *x, float *y, float z)
{
	*x = (*x - *y) * cos(0.8);
	*y = (*x + *y) * sin(0.8) - z;
}

void	draw_line(float x, float y, float x1, float y1, t_fdf *fdf)
{
	int		max;
	float	x_step;
	float	y_step;
	int		z;
	int		z1;
	char	*color1;

	z = ft_atoi(fdf->matrix[(int)y][(int)x]);
	z1 = ft_atoi(fdf->matrix[(int)y1][(int)x1]);
	fdf->color = 16777215 - (z * (3000 * z));
	color1 = ft_strchr(fdf->matrix[(int)y][(int)x], ',');
	if (color1)
		fdf->color = ft_atoi_base(color1 + 1, 16);
	x *= SCALE;
	y *= SCALE;
	x1 *= SCALE;
	y1 *= SCALE;
	isometric(&x, &y, z);
	isometric(&x1, &y1, z1);
	x += fdf->shift_x;
	y += fdf->shift_y;
	x1 += fdf->shift_x;
	y1 += fdf->shift_y;
	x_step = x1 - x;
	y_step = y1 - y;
	max = ft_max(ft_abs(x_step), ft_abs(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(x - x1) || (int)(y - y1))
	{
		mlx_pixel_put(fdf->mlx, fdf->win, x + 850, y + 250, fdf->color);
		x += x_step;
		y += y_step;
	}
}

void	draw(t_fdf *fdf)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			if (x < fdf->width - 1)
				draw_line(x, y, x + 1, y, fdf);
			if (y < fdf->height - 1)
				draw_line(x, y, x, y + 1, fdf);
			x++;
		}
		y++;
	}
}

int	ft_destroywindown(void)
{
	exit(EXIT_SUCCESS);
	return (0);
}

int	ft_presskey(int key, t_fdf *fdf)
{
	if (key == 53)
		ft_destroywindown();
	if (key == 126)
		fdf->shift_y -= 5;
	if (key == 125)
		fdf->shift_y += 5;
	if (key == 123)
		fdf->shift_x -= 5;
	if (key == 124)
		fdf->shift_x += 5;
	mlx_clear_window(fdf->mlx, fdf->win);
	draw(fdf);
	return (0);
}

int	main(int ac, char **av)
{
	t_fdf	fdf;

	if (ac != 2)
	{
		write(2, "Invalid arguments!\n", 19);
		exit(1);
	}
	fdf = parser(av[1]);
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, 3000, 1800, "FDF");
	draw(&fdf);
	mlx_hook(fdf.win, BUTTONPRESS, 1, ft_presskey, &fdf);
	mlx_hook(fdf.win, DESTROYPRESS, 0,
		ft_destroywindown, NULL);
	mlx_loop(fdf.mlx);
	return (0);
}
