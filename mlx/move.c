/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahri <ntahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 15:00:40 by ntahri            #+#    #+#             */
/*   Updated: 2026/04/18 15:00:42 by ntahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_forward_backward(t_player *p, char **map, int dir)
{
	double	new_x;
	double	new_y;

	new_x = p->pos_x + p->dir_x * MOVE_SPEED * dir;
	new_y = p->pos_y + p->dir_y * MOVE_SPEED * dir;
	if (map[(int)p->pos_y][(int)new_x] != '1')
		p->pos_x = new_x;
	if (map[(int)new_y][(int)p->pos_x] != '1')
		p->pos_y = new_y;
}

static void	move_strafe(t_player *p, char **map, int dir)
{
	double	new_x;
	double	new_y;

	new_x = p->pos_x + p->plane_x * MOVE_SPEED * dir;
	new_y = p->pos_y + p->plane_y * MOVE_SPEED * dir;
	if (map[(int)p->pos_y][(int)new_x] != '1')
		p->pos_x = new_x;
	if (map[(int)new_y][(int)p->pos_x] != '1')
		p->pos_y = new_y;
}

static void	rotate_player(t_player *p, int dir)
{
	double	old_dir_x;
	double	old_plane_x;
	double	speed;

	speed = ROT_SPEED * dir;
	old_dir_x = p->dir_x;
	p->dir_x = p->dir_x * cos(speed) - p->dir_y * sin(speed);
	p->dir_y = old_dir_x * sin(speed) + p->dir_y * cos(speed);
	old_plane_x = p->plane_x;
	p->plane_x = p->plane_x * cos(speed) - p->plane_y * sin(speed);
	p->plane_y = old_plane_x * sin(speed) + p->plane_y * cos(speed);
}

void	move_player(t_data *data)
{
	if (data->keys.w)
		move_forward_backward(&data->player, data->map, 1);
	if (data->keys.s)
		move_forward_backward(&data->player, data->map, -1);
	if (data->keys.a)
		move_strafe(&data->player, data->map, -1);
	if (data->keys.d)
		move_strafe(&data->player, data->map, 1);
	if (data->keys.left)
		rotate_player(&data->player, -1);
	if (data->keys.right)
		rotate_player(&data->player, 1);
}
