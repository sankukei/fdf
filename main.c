/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leothoma <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 17:30:23 by leothoma          #+#    #+#             */
/*   Updated: 2024/12/16 17:30:23 by leothoma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "header.h"
#include <unistd.h>

typedef	struct	s_data
{
	void	*img;
	char	*addr;
	int	bytes_per_pixel;
	int	line_length;
	int	endian;
}	t_data;

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bytes_per_pixel / 8));
	*(unsigned *)dst = color;
}

double	rescale(int value, double in_max, double out_min, double out_max)
{
	return out_min + (value * (out_max - out_min) / in_max);
}

int	color_picker(float count, float max_itter)
{
	
	max_itter++;
	if (count <= 0.01)
		return (0xffffff);
	if (count < 0.02)
		return (0xf9fff5);
	else if (count < 0.05)
		return (0xffffff);
	else if (count < 0.1)
		return (0x00ff00);
	else if (count < 0.5)
		return (0xff00ff);
	else
		return (0x0000ff);
}

int	create_img(void *img)
{
//	(void)img;
	s_coordo	cordo;
	s_fractal	fractal;
	cordo.x1 = -2.1;
	cordo.x2 = 0.6;
	cordo.y1 = -1.2;
	cordo.y2 = 1.2;
	cordo.screen_width = 1000;
	cordo.screen_height = 1000;
	cordo.zoom = 2;
	float	i = 0;
	float	j = 0;
	float	count = 0;
	double	tmp = 0;
	float	max_itter = 10.0;
	
	while (i++ < cordo.screen_width)
	{
		while (j++ < cordo.screen_height)
		{
			count = 0;
			fractal.x = rescale(i, 1000, -2, 2) / cordo.zoom;
			fractal.y = rescale(j, 1000, 2, -2) / cordo.zoom;
			fractal.c1 = fractal.x;
			fractal.c2 = fractal.y;

			while (count <= 10)
			{
				tmp = fractal.x;
				fractal.x = (fractal.x * fractal.x) - (fractal.y * fractal.y);
				fractal.y = 2 * tmp * fractal.y;
				fractal.x = fractal.x + fractal.c1;
				fractal.y = fractal.y + fractal.c2;
				if ((fractal.x * fractal.x) + (fractal.y * fractal.y) > 4)
				{
					my_mlx_pixel_put(img, i, j, color_picker(count, max_itter));
					break;
				}
				count += 0.01;
			}
			if (count >= 10)
				my_mlx_pixel_put(img, i, j, 0x000000);
		}
		j = 0;
	}
	return (0);
}

int	close_win(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

int	key_hook(int keycode, t_vars *vars)
{
	(void)vars;
	keycode++;
	//printf("%d", keycode);
	//printf("xdsfkljsflkjsdflkj");
	return (0);
}

int	mouse_hook(int keycode, s_coordo *cordo, void *img)
{
	if (keycode == 4)
	{
		cordo->zoom += 0.2;
		create_img(img);
		write(1, "MW UP", 5);
	}
	return (0);
}
int	main(void)
{
	t_data	img;
	t_vars	vars;
	s_coordo cordo;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1000, 1000, "fractal");
	img.img = mlx_new_image(vars.mlx, 1000, 1000);
	img.addr = mlx_get_data_addr(img.img, &img.bytes_per_pixel, &img.line_length, &img.endian);


	create_img(&img);

	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	//	window  keypress mask fn  image adress
//	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 2, 1L<<0, close_win, &cordo);
	mlx_mouse_hook(vars.win, mouse_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
