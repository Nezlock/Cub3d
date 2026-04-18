/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahri <ntahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 14:59:52 by ntahri            #+#    #+#             */
/*   Updated: 2026/04/18 14:59:53 by ntahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_dir_ns(t_player *p)
{
	if (p->spawn_dir == 'N')
	{
		p->dir_x = 0;
		p->dir_y = -1;
		p->plane_x = 0.66;
		p->plane_y = 0;
	}
	else
	{
		p->dir_x = 0;
		p->dir_y = 1;
		p->plane_x = -0.66;
		p->plane_y = 0;
	}
}

static void	set_dir_ew(t_player *p)
{
	if (p->spawn_dir == 'E')
	{
		p->dir_x = 1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = 0.66;
	}
	else
	{
		p->dir_x = -1;
		p->dir_y = 0;
		p->plane_x = 0;
		p->plane_y = -0.66;
	}
}

void	init_player(t_data *data)
{
	data->player.pos_x += 0.5;
	data->player.pos_y += 0.5;
	if (data->player.spawn_dir == 'N'
		|| data->player.spawn_dir == 'S')
		set_dir_ns(&data->player);
	else
		set_dir_ew(&data->player);
}
