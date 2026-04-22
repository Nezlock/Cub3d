/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahri <ntahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 14:58:37 by ntahri            #+#    #+#             */
/*   Updated: 2026/04/22 17:55:00 by ntahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_colors(t_textures *t)
{
	t->floor_color = (t->floor[0] << 16)
		| (t->floor[1] << 8) | t->floor[2];
	t->ceiling_color = (t->ceiling[0] << 16)
		| (t->ceiling[1] << 8) | t->ceiling[2];
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (write(2, "Error\nUsage: ./cub3D <map.cub>\n", 31), 1);
	if (!check_extension(argv[1]))
		return (write(2, "Error\nFile must have .cub extension\n", 36), 1);
	init_all(&data);
	data.raw_file = parser(argv[1], &data);
	parse_config(data.raw_file, &data);
	free_map(data.raw_file);
	data.raw_file = NULL;
	check_all(&data);
	init_player(&data);
	init_colors(&data.textures);
	if (!init_mlx(&data))
	{
		free_all(&data);
		return (write(2, "Error\nMLX init failed\n", 22), 1);
	}
	init_textures_mlx(&data);
	setup_hooks(&data);
	mlx_loop(data.mlx.mlx);
	return (0);
}
