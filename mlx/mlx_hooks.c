/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahri <ntahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 15:00:27 by ntahri            #+#    #+#             */
/*   Updated: 2026/04/18 15:00:29 by ntahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	key_press(int key, t_data *data)
{
	if (key == KEY_ESC)
		clean_exit(data);
	if (key == KEY_W)
		data->keys.w = 1;
	if (key == KEY_A)
		data->keys.a = 1;
	if (key == KEY_S)
		data->keys.s = 1;
	if (key == KEY_D)
		data->keys.d = 1;
	if (key == KEY_LEFT)
		data->keys.left = 1;
	if (key == KEY_RIGHT)
		data->keys.right = 1;
	return (0);
}

static int	key_release(int key, t_data *data)
{
	if (key == KEY_W)
		data->keys.w = 0;
	if (key == KEY_A)
		data->keys.a = 0;
	if (key == KEY_S)
		data->keys.s = 0;
	if (key == KEY_D)
		data->keys.d = 0;
	if (key == KEY_LEFT)
		data->keys.left = 0;
	if (key == KEY_RIGHT)
		data->keys.right = 0;
	return (0);
}

void	setup_hooks(t_data *data)
{
	mlx_hook(data->mlx.win, 2, 1L << 0, (void *)key_press, data);
	mlx_hook(data->mlx.win, 3, 1L << 1, (void *)key_release, data);
	mlx_hook(data->mlx.win, 17, 0, (void *)handle_destroy, data);
	mlx_loop_hook(data->mlx.mlx, (void *)render, data);
}
