/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahri <ntahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 14:59:56 by ntahri            #+#    #+#             */
/*   Updated: 2026/04/22 18:02:22 by ntahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_path(t_path *path)
{
	path->north = NULL;
	path->south = NULL;
	path->east = NULL;
	path->west = NULL;
}

void	init_textures(t_textures *textures)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		textures->floor[i] = -1;
		textures->ceiling[i] = -1;
		i++;
	}
	textures->floor_color = 0;
	textures->ceiling_color = 0;
}

void	init_data(t_data *data)
{
	data->map = NULL;
	data->raw_file = NULL;
	data->m_raw = 0;
	data->m_col = 0;
	data->player.pos_x = 0;
	data->player.pos_y = 0;
	data->player.dir_x = 0;
	data->player.dir_y = 0;
	data->player.plane_x = 0;
	data->player.plane_y = 0;
	data->player.spawn_dir = 0;
	data->keys.w = 0;
	data->keys.a = 0;
	data->keys.s = 0;
	data->keys.d = 0;
	data->keys.left = 0;
	data->keys.right = 0;
}

void	init_mlx_data(t_data *data)
{
	int	i;

	data->mlx.mlx = NULL;
	data->mlx.win = NULL;
	data->mlx.img = NULL;
	data->mlx.addr = NULL;
	i = 0;
	while (i < 4)
	{
		data->tex[i].img = NULL;
		data->tex[i].addr = NULL;
		i++;
	}
}

void	init_all(t_data *data)
{
	init_data(data);
	init_path(&data->path);
	init_textures(&data->textures);
	init_mlx_data(data);
}
