/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahri <ntahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18 15:00:20 by ntahri            #+#    #+#             */
/*   Updated: 2026/04/18 15:00:22 by ntahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_exit(t_data *data)
{
	free_all(data);
	exit(0);
}

int	handle_destroy(t_data *data)
{
	clean_exit(data);
	return (0);
}
