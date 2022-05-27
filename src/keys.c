/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 17:58:07 by moabid            #+#    #+#             */
/*   Updated: 2022/05/27 16:40:13 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/macros.h"
#include "../includes/fdf.h"

void	rotate(int key, t_fdf *fdf)
{
	if (key == NUM_PAD_2)
		fdf->camera->alpha += ALPHA;
	else if (key == NUM_PAD_8)
		fdf->camera->alpha -= ALPHA;
	else if (key == NUM_PAD_4)
		fdf->camera->beta -= BETA;
	else if (key == NUM_PAD_6)
		fdf->camera->beta += BETA;
	drawer(fdf->map, fdf);
}

void	zoom(int key, t_fdf *fdf)
{
	if (key == NUM_PAD_PLUS)
		fdf->camera->zoom+=ZOOM;
	else if (key == NUM_PAD_MINUS)
		fdf->camera->zoom-=ZOOM;
	if (fdf->camera->zoom < 1)
		fdf->camera->zoom = 1;
	drawer(fdf->map, fdf);
}

void	move(int key, t_fdf *fdf)
{
	if (key == ARROW_LEFT)
		fdf->camera->x_offset -= X_OFFSET;
	else if (key == ARROW_RIGHT)
		fdf->camera->x_offset += X_OFFSET;
	else if (key == ARROW_UP)
		fdf->camera->y_offset -= Y_OFFSET;
	else
		fdf->camera->y_offset += Y_OFFSET;
	drawer(fdf->map, fdf);
}

void	threedialization(int key, t_fdf *fdf)
{
	fdf->camera->alpha = 0;
	fdf->camera->beta = 0;
	fdf->camera->gamma = 0;
	if (key == NUM_PAD_1)
		fdf->camera->projection = twoD;
	else if (key == NUM_PAD_3)
		fdf->camera->projection = threeD;
	drawer(fdf->map, fdf);
}

void	help(int key, t_fdf *fdf)
{
	if (key == NUM_PAD_5)
		fdf->camera->help = with;
	else if (key == NUM_PAD_0)
		fdf->camera->help = without;
	drawer(fdf->map, fdf);
}
