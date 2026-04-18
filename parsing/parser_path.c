/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahri <ntahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 15:00:09 by ntahri            #+#    #+#             */
/*   Updated: 2026/04/18 15:00:12 by ntahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && ft_isspace(line[i]))
		i++;
	return (line[i] == '1' || line[i] == '0');
}

void	fill_color(char *line, int *color, t_data *data)
{
	int	i;

	i = 1;
	while (ft_isspace(line[i]))
		i++;
	color[0] = ft_atoi(line + i);
	while (line[i] && line[i] != ',')
		i++;
	if (!line[i])
		ft_error(data, ERR_COLOR);
	i++;
	color[1] = ft_atoi(line + i);
	while (line[i] && line[i] != ',')
		i++;
	if (!line[i])
		ft_error(data, ERR_COLOR);
	i++;
	color[2] = ft_atoi(line + i);
}

char	*fill_path(char *src)
{
	int		i;
	int		len;
	char	*dest;

	i = 2;
	while (ft_isspace(src[i]))
		i++;
	dest = ft_strdup(src + i);
	if (!dest)
		return (NULL);
	len = ft_strlen(dest);
	while (len > 0 && ft_isspace(dest[len - 1]))
		len--;
	dest[len] = '\0';
	return (dest);
}

void	dispatch(char *line, t_data *data)
{
	if (line[0] == 'N' && line[1] == 'O' && data->path.north == NULL)
		data->path.north = fill_path(line);
	else if (line[0] == 'E' && line[1] == 'A' && data->path.east == NULL)
		data->path.east = fill_path(line);
	else if (line[0] == 'W' && line[1] == 'E' && data->path.west == NULL)
		data->path.west = fill_path(line);
	else if (line[0] == 'S' && line[1] == 'O' && data->path.south == NULL)
		data->path.south = fill_path(line);
	else if (line[0] == 'F' && data->textures.floor[0] == -1)
	{
		check_color_line(line, data);
		fill_color(line, data->textures.floor, data);
	}
	else if (line[0] == 'C' && data->textures.ceiling[0] == -1)
	{
		check_color_line(line, data);
		fill_color(line, data->textures.ceiling, data);
	}
	else
		ft_error(data, ERR_SYNTAX);
}

void	parse_config(char **raw, t_data *data)
{
	int	i;

	i = 0;
	while (raw[i] && !is_map_line(raw[i]))
	{
		if (raw[i][0] != '\0')
			dispatch(raw[i], data);
		i++;
	}
	if (!raw[i] || !is_map_line(raw[i]))
		ft_error(data, ERR_NOMAP);
	fill_map(data, raw + i);
}
