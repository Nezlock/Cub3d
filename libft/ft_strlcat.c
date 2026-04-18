/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:31:50 by ntahri            #+#    #+#             */
/*   Updated: 2024/11/28 18:31:52 by ntahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	ld;
	size_t	ls;

	ld = ft_strlen(dst);
	ls = ft_strlen(src);
	i = 0;
	if (size <= ld)
		return (ls + size);
	while (src[i] && (ld + i) < (size - 1))
	{
		dst[i + ld] = src[i];
		i++;
	}
	dst[i + ld] = '\0';
	return (ld + ls);
}
