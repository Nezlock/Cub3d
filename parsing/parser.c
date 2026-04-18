/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahri <ntahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 15:00:14 by ntahri            #+#    #+#             */
/*   Updated: 2026/04/18 15:00:16 by ntahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_line(char	*file, t_data *map)
{
	int		fd;
	char	*line;
	int		line_count;

	line_count = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		ft_error(map, ERR_FILE);
	else
	{
		line = get_next_line(fd);
		while (line)
		{
			line_count++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	return (line_count);
}

void	trim(char	*line)
{
	char	*pos;

	pos = ft_strchr(line, '\n');
	if (pos)
		*pos = '\0';
}

char	**parser(char	*line, t_data *map)
{
	char	**file;
	int		fd;
	int		count;
	int		i;

	i = 0;
	count = count_line(line, map);
	fd = open(line, O_RDONLY);
	if (fd < 0)
		ft_error(map, ERR_FILE);
	file = malloc (sizeof(char *) * (count + 1));
	if (!file)
		ft_error(map, ERR_MALLOC);
	file[count] = NULL;
	while (i < count)
	{
		file[i] = get_next_line(fd);
		trim(file[i]);
		i++;
	}
	close(fd);
	return (file);
}
