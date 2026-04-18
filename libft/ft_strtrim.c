/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:26:52 by ntahri            #+#    #+#             */
/*   Updated: 2024/11/29 16:12:18 by ntahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check(char const *s1, char c)
{
	int				i;
	unsigned char	*set;

	i = 0;
	set = (unsigned char *)s1;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, const char *set)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(s1) - 1;
	if (*s1 == 0)
		return (ft_strdup((char *)s1));
	if (*set == 0)
		return (ft_strdup(s1));
	while (s1[i] && ft_check(set, s1[i]))
		i++;
	while (j > i && ft_check(set, s1[j]))
		j--;
	return (ft_substr(s1, i, j - i + 1));
}
