/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahri <ntahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 14:59:07 by ntahri            #+#    #+#             */
/*   Updated: 2026/04/18 14:59:09 by ntahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_wall_stripe(t_data *data, t_ray *ray, int x, t_tex *tex)
{
	double	step;
	double	tex_pos;
	int		tex_y;
	int		y;

	step = (double)tex->height / ray->line_height;
	tex_pos = (ray->draw_start - WIN_H / 2
			+ ray->line_height / 2) * step;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)tex_pos % tex->height;
		tex_pos += step;
		put_pixel(&data->mlx, x, y,
			get_tex_pixel(tex, ray->tex_x, tex_y));
		y++;
	}
}

int	get_tex_pixel(t_tex *tex, int x, int y)
{
	char	*dst;

	dst = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)dst);
}
