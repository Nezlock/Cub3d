/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahri <ntahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 14:59:46 by ntahri            #+#    #+#             */
/*   Updated: 2026/04/18 14:59:48 by ntahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "cub3d.h"

void	check_path(t_path	*path, t_data *map)
{
	if (!path->north || !path->east || !path->west || !path->south)
		ft_error(map, ERR_PATH);
}

void	check_color(t_textures	*textures, t_data *map)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if ((textures->floor[i] < 0)
			|| ((textures->floor[i]) > 255))
			ft_error(map, ERR_COLOR);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if ((textures->ceiling[i] < 0)
			|| (textures->ceiling[i] > 255))
			ft_error(map, ERR_COLOR);
		i++;
	}
}

void	check_all(t_data *map)
{
	check_path(&map->path, map);
	check_color(&map->textures, map);
	check_map(map);
}

int	check_extension(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 5)
		return (0);
	return (ft_strncmp(file + len - 4, ".cub", 4) == 0);
}

void	check_color_line(char *line, t_data *data)
{
	int	i;
	int	commas;
	int	has_digit;

	i = 1;
	commas = 0;
	has_digit = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]))
			has_digit = 1;
		else if (line[i] == ',')
		{
			if (!has_digit)
				ft_error(data, ERR_COLOR);
			commas++;
			has_digit = 0;
		}
		else if (!ft_isspace(line[i]))
			ft_error(data, ERR_COLOR);
		i++;
	}
	if (commas != 2 || !has_digit)
		ft_error(data, ERR_COLOR);
}
