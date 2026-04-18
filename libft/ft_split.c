/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:26:25 by ntahri            #+#    #+#             */
/*   Updated: 2024/11/29 16:16:57 by ntahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	countwords(const char *str, char c)
{
	int	i;
	int	word;

	word = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
		{
			word++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (word);
}

static char	**ft_free(char **s, int j)
{
	while (j >= 0)
	{
		free(s[j]);
		j--;
	}
	free(s);
	return (NULL);
}

char	*ft_fill(char const *s, char c, int i)
{
	int		j;
	int		k;
	char	*dest;

	j = i;
	while (s[i] && s[i] != c)
		i++;
	dest = malloc(sizeof(char) * ((i - j) + 1));
	if (dest == NULL)
		return (NULL);
	k = 0;
	while (j != i)
	{
		dest[k] = s[j];
		k++;
		j++;
	}
	dest[k] = '\0';
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;

	tab = (char **)malloc(sizeof(char *) * (countwords(s, c) + 1));
	if (tab == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			tab[j] = ft_fill(s, c, i);
			if (!tab[j])
				return (ft_free(tab, j));
			i += ft_strlen(tab[j]);
			j++;
		}
		else
			i++;
	}
	tab[j] = NULL;
	return (tab);
}
