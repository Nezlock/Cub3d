/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahri <ntahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 14:59:31 by ntahri            #+#    #+#             */
/*   Updated: 2026/04/18 14:59:32 by ntahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	calc_wall_height(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	ray->line_height = (int)(WIN_H / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + WIN_H / 2;
	if (ray->draw_end >= WIN_H)
		ray->draw_end = WIN_H - 1;
}

static t_tex	*choose_texture(t_data *data, t_ray *ray)
{
	if (ray->side == 0 && ray->dir_x > 0)
		return (&data->tex[TEX_WE]);
	if (ray->side == 0 && ray->dir_x < 0)
		return (&data->tex[TEX_EA]);
	if (ray->side == 1 && ray->dir_y > 0)
		return (&data->tex[TEX_NO]);
	return (&data->tex[TEX_SO]);
}

static int	calc_tex_x(t_ray *ray, t_player *p, t_tex *tex)
{
	double	wall_x;
	int		tex_x;

	if (ray->side == 0)
		wall_x = p->pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		wall_x = p->pos_x + ray->perp_wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if (ray->side == 0 && ray->dir_x > 0)
		tex_x = tex->width - tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		tex_x = tex->width - tex_x - 1;
	if (tex_x < 0)
		tex_x = 0;
	if (tex_x >= tex->width)
		tex_x = tex->width - 1;
	return (tex_x);
}

void	draw_column(t_data *data, t_ray *ray, int x)
{
	t_tex	*tex;
	int		y;

	tex = choose_texture(data, ray);
	ray->tex_x = calc_tex_x(ray, &data->player, tex);
	y = 0;
	while (y < ray->draw_start)
	{
		put_pixel(&data->mlx, x, y, data->textures.ceiling_color);
		y++;
	}
	draw_wall_stripe(data, ray, x, tex);
	y = ray->draw_end + 1;
	while (y < WIN_H)
	{
		put_pixel(&data->mlx, x, y, data->textures.floor_color);
		y++;
	}
}
