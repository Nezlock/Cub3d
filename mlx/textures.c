/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahri <ntahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 15:00:44 by ntahri            #+#    #+#             */
/*   Updated: 2026/04/18 15:00:46 by ntahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_texture(t_data *data, t_tex *tex, char *path)
{
	tex->img = mlx_xpm_file_to_image(data->mlx.mlx,
			path, &tex->width, &tex->height);
	if (!tex->img)
		ft_error(data, ERR_PATH);
	tex->addr = mlx_get_data_addr(tex->img,
			&tex->bpp, &tex->line_len, &tex->endian);
}

void	init_textures_mlx(t_data *data)
{
	load_texture(data, &data->tex[TEX_NO], data->path.north);
	load_texture(data, &data->tex[TEX_SO], data->path.south);
	load_texture(data, &data->tex[TEX_EA], data->path.east);
	load_texture(data, &data->tex[TEX_WE], data->path.west);
}
