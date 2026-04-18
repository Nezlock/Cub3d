/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahri <ntahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 14:59:40 by ntahri            #+#    #+#             */
/*   Updated: 2026/04/18 14:59:42 by ntahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**copy_map(char **map, int rows, t_data *data)
{
	char	**copy;
	int		i;

	i = 0;
	copy = malloc(sizeof(char *) * (rows + 1));
	if (!copy)
		ft_error(data, ERR_MALLOC);
	while (i < rows)
	{
		copy[i] = ft_strdup(map[i]);
		i++;
	}
	copy[rows] = NULL;
	return (copy);
}

int	flood_fill(char **map, int x, int y)
{
	if (y < 0 || !map[y] || x < 0
		|| !map[y][x] || map[y][x] == ' ')
		return (0);
	if (map[y][x] == '1' || map[y][x] == 'V')
		return (1);
	map[y][x] = 'V';
	if (!flood_fill(map, x + 1, y))
		return (0);
	if (!flood_fill(map, x - 1, y))
		return (0);
	if (!flood_fill(map, x, y + 1))
		return (0);
	if (!flood_fill(map, x, y - 1))
		return (0);
	return (1);
}

static void	check_cell(char c, t_data *data, int *count, int pos[2])
{
	if (!ft_strchr("01NSEW ", c))
		ft_error(data, ERR_CHAR);
	if (ft_strchr("NSEW", c))
	{
		(*count)++;
		data->player.pos_x = pos[0];
		data->player.pos_y = pos[1];
		data->player.spawn_dir = c;
	}
}

void	check_chars(char **map, t_data *data)
{
	int	i;
	int	j;
	int	count;
	int	pos[2];

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			pos[0] = j;
			pos[1] = i;
			check_cell(map[i][j], data, &count, pos);
			j++;
		}
		i++;
	}
	if (count != 1)
		ft_error(data, ERR_PLAYER);
}

void	check_map(t_data *data)
{
	char	**copy;

	check_chars(data->map, data);
	copy = copy_map(data->map, data->m_raw, data);
	if (!flood_fill(copy, (int)data->player.pos_x,
			(int)data->player.pos_y))
	{
		free_map(copy);
		ft_error(data, ERR_MAP);
	}
	free_map(copy);
}
