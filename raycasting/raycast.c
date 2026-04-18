/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahri <ntahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 14:59:16 by ntahri            #+#    #+#             */
/*   Updated: 2026/04/18 14:59:17 by ntahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	raycast(t_data *data)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIN_W)
	{
		init_ray_dir(&ray, &data->player, x);
		init_ray_step(&ray, &data->player);
		perform_dda(&ray, data);
		calc_wall_height(&ray);
		draw_column(data, &ray, x);
		x++;
	}
}
