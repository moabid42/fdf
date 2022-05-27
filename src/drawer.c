/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 11:13:03 by moabid            #+#    #+#             */
/*   Updated: 2022/05/27 22:07:16 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/error.h"

static void	put_pixel(t_fdf *fdf, int x, int y, int color)
{
	int		i;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		i = (x * fdf->bits_per_pixel / 8) + (y * fdf->size_line);
		fdf->data_addr[i] = color;
		fdf->data_addr[++i] = color >> 8;
		fdf->data_addr[++i] = color >> 16;
	}
}

static void	draw_line(t_point f, t_point s, t_fdf *fdf)
{
	t_point	delta;
	t_point	sign;
	t_point	cur;
	int		error[2];

	delta.x = abs(s.x - f.x);
	delta.y = abs(s.y - f.y);
	sign.x = signOf(f.x, s.x);
	sign.y = signOf(f.y, s.y);
	error[0] = delta.x - delta.y;
	cur = f;
	while (cur.x != s.x || cur.y != s.y)
	{
		put_pixel(fdf, cur.x, cur.y, get_color(cur, f, s, delta));
		if ((error[1] = error[0] * 2) > -delta.y)
		{
			error[0] -= delta.y;
			cur.x += sign.x;
		}
		if (error[1] < delta.x)
		{
			error[0] += delta.x;
			cur.y += sign.y;
		}
	}
}

void	print_menu(t_fdf *fdf)
{
	int		y;
	void	*mlx;
	void	*win;

	y = 0;
	mlx = fdf->mlx;
	win = fdf->win;
	mlx_string_put(mlx, win, 15, y += 20, TEXT_COLOR, "How to Use :");
	mlx_string_put(mlx, win, 55, y += 35, TEXT_COLOR_2, "Zoom:");
	mlx_string_put(mlx, win, 135, y, TEXT_COLOR, "+/-");
	mlx_string_put(mlx, win, 55, y += 35, TEXT_COLOR_2, "Move:");
	mlx_string_put(mlx, win, 135, y, TEXT_COLOR, "Arrows");
	mlx_string_put(mlx, win, 55, y += 35, TEXT_COLOR_2, "Rotate:");
	mlx_string_put(mlx, win, 135, y, TEXT_COLOR, "Using Num Pad");
	mlx_string_put(mlx, win, 55, y += 35, TEXT_COLOR_2, "Projection ~");
	mlx_string_put(mlx, win, 77, y += 25, TEXT_COLOR, "2D: Num_1 Key");
	mlx_string_put(mlx, win, 77, y += 25, TEXT_COLOR, "3D: Num_3 Key");
	mlx_string_put(mlx, win, 55, y += 35, TEXT_COLOR_2, "Hide Help :");
	mlx_string_put(mlx, win, 135, y, TEXT_COLOR, "Num_0 Key");
	mlx_string_put(mlx, win, 55, y += 50, TEXT_COLOR_2, "QUIT:");
	mlx_string_put(mlx, win, 135, y, TEXT_COLOR, "ESC");
	mlx_string_put(mlx, win, 870, 950, TEXT_COLOR_2, "BEASTS DON'T NEED A MOUSE ...");
}

void	print_help(t_fdf *fdf)
{
	int		y;
	void	*mlx;
	void	*win;

	y = 0;
	mlx = fdf->mlx;
	win = fdf->win;
	mlx_string_put(mlx, win, 931, y += 40, TEXT_COLOR_2, "Welcome !");
	mlx_string_put(mlx, win, 840, y += 30, TEXT_COLOR, "Press NUM_5 Key to Display the Menu !");
	
}

void		drawer(t_map *map, t_fdf *fdf)
{
	int		x;
	int		y;

	init_background(fdf);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (x != fdf->map->width - 1)
				draw_line(project(new_point(x, y, map), fdf),
					project(new_point(x + 1, y, map), fdf), fdf);
			if (y != fdf->map->height - 1)
				draw_line(project(new_point(x, y, map), fdf),
					project(new_point(x, y + 1, map), fdf), fdf);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	if (fdf->camera->help == with)
		print_menu(fdf);
	else
		print_help(fdf);
}

