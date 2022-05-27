/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:21:30 by moabid            #+#    #+#             */
/*   Updated: 2022/05/27 16:46:01 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/error.h"

t_coord_val	*new_coord(char *s)
{
	t_coord_val	*coord;
	char		**parts;

	if (!(coord = (t_coord_val *)ft_malloc(sizeof(t_coord_val))))
		error(MAP_READING);
	if (!(parts = ft_split(s, ',')))
		error(MAP_READING);
	if (!ft_isnumber(parts[0], 10))
		error(MAP_READING);
	if (parts[1] && !ft_isnumber(parts[1], 16))
		error(MAP_READING);
	coord->z = ft_atoi(parts[0]);
	coord->color = (parts[1] ? ft_atoi_base(parts[1], 16) : -1);
	coord->next = NULL;
	free_split_arr(parts);
	return (coord);
}


void	push_line(char **coords_line, t_coord_val **stack, t_map *map)
{
	int	width;

	width = 0;
	while (*coords_line)
	{
		push(stack, new_coord(*(coords_line++)));
		width++;
	}
	if (map->height == 0)
		map->width = width;
	else if (map->width != width)
		error(MAP);
}

void	read_map(const int fd, t_coord_val **stack, t_map *map)
{
	char	*line;
	char	**coords_line;

	line = get_next_line(fd);
	while (line)
	{
		new_line_remove(line);
		coords_line = ft_split(line, ' ');
		if (!coords_line)
			error(MAP_READING);
		push_line(coords_line, stack, map);
		free_split_arr(coords_line);
		ft_strdel(&line);
		map->height++;
		line = get_next_line(fd);
	}
	if (!(*stack))
		error(MAP);
}
