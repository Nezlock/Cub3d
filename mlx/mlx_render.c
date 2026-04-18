/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahri <ntahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 15:00:36 by ntahri            #+#    #+#             */
/*   Updated: 2026/04/18 15:00:38 by ntahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	dst = mlx->addr + (y * mlx->line_len + x * (mlx->bpp / 8));
	*(unsigned int *)dst = color;
}

int	render(t_data *data)
{
	move_player(data);
	raycast(data);
	mlx_put_image_to_window(data->mlx.mlx, data->mlx.win,
		data->mlx.img, 0, 0);
	return (0);
}
