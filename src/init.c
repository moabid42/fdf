/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:22:43 by moabid            #+#    #+#             */
/*   Updated: 2022/05/27 17:44:45 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/error.h"

void	init_background(t_fdf *fdf)
{
	int	*image;
	int	i;

	ft_bzero(fdf->data_addr, WIDTH * HEIGHT * (fdf->bits_per_pixel / 8));
	image = (int *)(fdf->data_addr);
	i = 0;
	while (i < HEIGHT * WIDTH)
	{
		image[i] = BACKGROUND;
		i++;
	}
}

t_map	*map_init(void)
{
	t_map	*map;

	map = (t_map *)ft_malloc(sizeof(t_map));
	map->width = 0;
	map->height = 0;
	map->coords_arr = NULL;
	map->colors_arr = NULL;
	map->z_min = MAX;
	map->z_max = MIN;
	map->z_range = 0;
	return (map);
}

t_camera	*camera_init(t_fdf *fdf)
{
	t_camera	*camera;

	if (!(camera = (t_camera *)ft_malloc(sizeof(t_camera))))
		error(CAMERA_INIT);
	camera->zoom = ft_min(WIDTH / fdf->map->width / 2,
						HEIGHT / fdf->map->height / 2);
	camera->alpha = 0;
	camera->beta = 0;
	camera->gamma = 0;
	camera->z_divisor = 1;
	camera->x_offset = 0;
	camera->y_offset = 0;
	return (camera);
}

t_fdf		*fdf_init(t_map *map)
{
	t_fdf	*fdf;

	if (!(fdf = (t_fdf *)ft_malloc(sizeof(t_fdf))))
		error(FDF_INIT);
	if (!(fdf->mlx = mlx_init()))
		error(FDF_INIT);
	if (!(fdf->win = mlx_new_window(fdf->mlx, WIDTH, HEIGHT, "FdF")))
		error(FDF_INIT);
	if (!(fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT)))
		error(FDF_INIT);
	fdf->data_addr = mlx_get_data_addr(fdf->img, &(fdf->bits_per_pixel),
										&(fdf->size_line), &(fdf->endian));
	fdf->map = map;
	if (!(fdf->mouse = (t_mouse *)ft_malloc(sizeof(t_mouse))))
		error(FDF_INIT);
	return (fdf);
}