/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahri <ntahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 15:00:32 by ntahri            #+#    #+#             */
/*   Updated: 2026/04/18 15:00:33 by ntahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	create_image(t_data *data)
{
	t_mlx	*m;

	m = &data->mlx;
	m->img = mlx_new_image(m->mlx, WIN_W, WIN_H);
	if (!m->img)
		return (0);
	m->addr = mlx_get_data_addr(m->img, &m->bpp,
			&m->line_len, &m->endian);
	return (1);
}

static int	create_window(t_data *data)
{
	t_mlx	*m;

	m = &data->mlx;
	m->win = mlx_new_window(m->mlx, WIN_W, WIN_H, "cub3D");
	if (!m->win)
		return (0);
	return (1);
}

int	init_mlx(t_data *data)
{
	data->mlx.mlx = mlx_init();
	if (!data->mlx.mlx)
		return (0);
	if (!create_window(data))
		return (0);
	if (!create_image(data))
		return (0);
	return (1);
}
