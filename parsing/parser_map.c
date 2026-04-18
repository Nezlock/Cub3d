/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahri <ntahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 15:00:02 by ntahri            #+#    #+#             */
/*   Updated: 2026/04/18 15:00:05 by ntahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isspace(line[i]))
			return (0);
		i++;
	}
	return (1);
}

static char	*pad_line(char *src, int width, t_data *data)
{
	char	*line;
	int		len;
	int		i;

	len = ft_strlen(src);
	line = malloc(width + 1);
	if (!line)
		ft_error(data, ERR_MALLOC);
	i = -1;
	while (++i < len)
		line[i] = src[i];
	while (i < width)
		line[i++] = ' ';
	line[width] = '\0';
	return (line);
}

void	fill_map(t_data *data, char **file)
{
	int	count;
	int	max_w;
	int	i;

	count = 0;
	max_w = 0;
	while (file[count] && !is_empty_line(file[count]))
	{
		if ((int)ft_strlen(file[count]) > max_w)
			max_w = ft_strlen(file[count]);
		count++;
	}
	i = count - 1;
	while (file[++i])
		if (!is_empty_line(file[i]))
			ft_error(data, ERR_MAP);
	data->map = malloc(sizeof(char *) * (count + 1));
	if (!data->map)
		ft_error(data, ERR_MALLOC);
	data->m_raw = count;
	i = -1;
	while (++i < count)
		data->map[i] = pad_line(file[i], max_w, data);
	data->map[count] = NULL;
}
