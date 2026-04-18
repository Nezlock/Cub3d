/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahri <ntahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 14:58:51 by ntahri            #+#    #+#             */
/*   Updated: 2026/04/18 14:58:52 by ntahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_mlx(t_data *data)
{
	if (data->mlx.img && data->mlx.mlx)
		mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	if (data->mlx.win && data->mlx.mlx)
		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	if (data->mlx.mlx)
	{
		mlx_destroy_display(data->mlx.mlx);
		free(data->mlx.mlx);
	}
}

void	free_all(t_data *data)
{
	int	i;

	if (!data)
		return ;
	i = 0;
	while (i < 4)
	{
		if (data->tex[i].img && data->mlx.mlx)
			mlx_destroy_image(data->mlx.mlx, data->tex[i].img);
		i++;
	}
	free(data->path.north);
	free(data->path.south);
	free(data->path.east);
	free(data->path.west);
	if (data->map)
		free_map(data->map);
	free_mlx(data);
}

void	ft_error(t_data *data, char *msg)
{
	free_all(data);
	write(2, "Error\n", 6);
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(1);
}
