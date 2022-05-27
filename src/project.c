/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 15:08:33 by moabid            #+#    #+#             */
/*   Updated: 2022/05/27 22:34:51 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/error.h"
#include "math.h"

static void	rotate_x(int *y, int *z, double alpha)
{
	int	previous_y;

	previous_y = *y;
	*y = previous_y * cos(alpha) + *z * sin(alpha);
	*z = -previous_y * sin(alpha) + *z * cos(alpha);
}

static void	rotate_y(int *x, int *z, double beta)
{
	int	previous_x;

	previous_x = *x;
	*x = previous_x * cos(beta) + *z * sin(beta);
	*z = -previous_x * sin(beta) + *z * cos(beta);
}

void	iso(int *x, int *y, int z)
{
	int	previous_x;
	int	previous_y;

	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(0.83599);
	*y = -z + (previous_x + previous_y) * sin(0.599);
}

t_point	project(t_point p, t_fdf *fdf)
{
	p.x *= fdf->camera->zoom;
	p.y *= fdf->camera->zoom;
	p.z *= fdf->camera->zoom / fdf->camera->z_divisor;
	p.x -= (fdf->map->width * fdf->camera->zoom) / 2;
	p.y -= (fdf->map->height * fdf->camera->zoom) / 2;
	rotate_x(&p.y, &p.z, fdf->camera->alpha);
	rotate_y(&p.x, &p.z, fdf->camera->beta);
	if (fdf->camera->projection == threeD)
		iso(&p.x, &p.y, p.z);
	p.x += WIDTH / 2 + fdf->camera->x_offset;
	p.y += HEIGHT / 2 + fdf->camera->y_offset;
	return (p);
}
