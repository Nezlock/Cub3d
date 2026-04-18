/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:27:49 by ntahri            #+#    #+#             */
/*   Updated: 2024/11/29 16:13:31 by ntahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int				i;
	unsigned char	dest;

	dest = (unsigned char)c;
	i = 0;
	while (s[i] != dest)
	{
		if ((unsigned char)s[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)s + i);
}
