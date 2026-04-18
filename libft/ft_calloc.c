/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:28:22 by ntahri            #+#    #+#             */
/*   Updated: 2024/11/29 15:49:14 by ntahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*dest;

	if (nmemb == 0 || size == 0)
		return (dest = malloc(sizeof(char)));
	dest = malloc(size * nmemb);
	if (dest == NULL)
		return (NULL);
	ft_bzero(dest, nmemb * size);
	return (dest);
}
