/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 19:20:28 by moabid            #+#    #+#             */
/*   Updated: 2022/05/27 22:07:24 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/error.h"

int ft_min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

int ft_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

int	signOf(int a, int b)
{
	if (a < b)
		return (1);
	else
		return (-1);
}
