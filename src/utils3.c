/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 19:20:28 by moabid            #+#    #+#             */
/*   Updated: 2022/05/27 22:48:22 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/error.h"

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	sign_of(int a, int b)
{
	if (a < b)
		return (1);
	else
		return (-1);
}

t_point	ft_delta(t_point *f, t_point *s)
{
	t_point	delta;

	delta.x = abs(s->x - f->x);
	delta.y = abs(s->y - f->y);
	return (delta);
}

t_point	ft_sign(t_point *f, t_point *s)
{
	t_point	sign;

	sign.x = sign_of(f->x, s->x);
	sign.y = sign_of(f->y, s->y);
	return (sign);
}
