/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:39:29 by moabid            #+#    #+#             */
/*   Updated: 2022/05/27 22:30:36 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/macros.h"
#include "../includes/fdf.h"

int	key_press(int key, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (key == MAIN_PAD_ESC)
		exit(0);
	if (key == NUM_PAD_PLUS || key == NUM_PAD_MINUS)
		zoom(key, fdf);
	else if (key == ARROW_LEFT || key == ARROW_RIGHT
		|| key == ARROW_UP || key == ARROW_DOWN)
		move(key, fdf);
	else if (key == NUM_PAD_2 || key == NUM_PAD_8
		|| key == NUM_PAD_4 || key == NUM_PAD_6)
		rotate(key, fdf);
	else if (key == NUM_PAD_1 || key == NUM_PAD_3)
		threedialization(key, fdf);
	else if (key == NUM_PAD_5 || key == NUM_PAD_0)
		help(key, fdf);
	return (0);
}

void	setup_keys(t_fdf *fdf)
{
	mlx_hook(fdf->win, 2, 0, key_press, fdf);
	mlx_hook(fdf->win, 17, 0, ft_close, fdf);
}
