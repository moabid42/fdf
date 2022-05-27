/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moabid <moabid@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 19:45:10 by moabid            #+#    #+#             */
/*   Updated: 2022/05/27 16:36:56 by moabid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/error.h"

int	main(int argc, char **argv)
{
	int			fd;
	t_map		*map;
	t_coord_val	*stack;
	t_fdf		*fdf;

	stack = NULL;
	errno = 0;
	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (fd < 1)
			error(MAP);
		map = map_init();
		read_map(fd, &stack, map);
		fdf = fdf_init(map);
		save_to_map_array(&stack, map);
		fdf->camera = camera_init(fdf);
		drawer(fdf->map, fdf);
		setup_keys(fdf);
		mlx_loop(fdf->mlx);
	}
	error(USAGE);
	return (0);
}