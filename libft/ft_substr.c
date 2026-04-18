/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:28:12 by ntahri            #+#    #+#             */
/*   Updated: 2024/11/29 16:12:47 by ntahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;
	size_t	j;

	i = start;
	j = 0;
	if (start >= ft_strlen(s))
	{
		dest = malloc(1);
		if (dest == NULL)
			return (NULL);
		dest[0] = '\0';
		return (dest);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	dest = malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	while (i < ft_strlen(s) && j < len)
		dest[j++] = s[i++];
	dest[j] = '\0';
	return (dest);
}
