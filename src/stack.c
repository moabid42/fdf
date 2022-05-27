/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:26:02 by moabid            #+#    #+#             */
/*   Updated: 2022/05/27 22:40:53 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/error.h"

t_point	new_point(int x, int y, t_map *map)
{
	t_point	point;
	int		index;

	index = y * map->width + x;
	point.x = x;
	point.y = y;
	point.z = map->coords_arr[index];
	if (map->colors_arr[index] == -1)
		point.color = get_default_color(point.z, map);
	else
		point.color = map->colors_arr[index];
	return (point);
}

void	push(t_coord_val **stack, t_coord_val *new)
{
	if (stack)
	{
		if (new)
			new->next = *stack;
		*stack = new;
	}
}

t_coord_val	*pop(t_coord_val **stack)
{
	t_coord_val	*top;

	top = NULL;
	if (stack && *stack)
	{
		top = *stack;
		*stack = (*stack)->next;
	}
	return (top);
}

void	save_to_map_array(t_coord_val **stack, t_map *map)
{
	t_coord_val	*coord;
	ssize_t		i;
	size_t		arr_size;

	arr_size = map->width * map->height * sizeof(int);
	map->coords_arr = ft_malloc(arr_size);
	map->colors_arr = ft_malloc(arr_size);
	if (!map->colors_arr || !map->coords_arr)
		error(CONV_TO_ARR);
	i = map->width * map->height - 1;
	coord = pop(stack);
	while (coord && i >= 0)
	{
		map->coords_arr[i] = coord->z;
		map->colors_arr[i] = coord->color;
		if (coord->z > map->z_max)
			map->z_max = coord->z;
		if (coord->z < map->z_min)
			map->z_min = coord->z;
		i--;
		free(coord);
		coord = pop(stack);
	}
	map->z_range = map->z_max - map->z_min;
}
