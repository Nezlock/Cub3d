/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntahri <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:28:37 by ntahri            #+#    #+#             */
/*   Updated: 2024/11/28 18:44:08 by ntahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count(int n)
{
	int		i;
	long	cp;

	i = 0;
	cp = n;
	if (n < 0)
	{
		cp = -cp;
		i++;
	}
	else if (n == 0)
		i++;
	while (cp > 0)
	{
		cp = cp / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	cp;
	char	*str;
	int		size;

	size = ft_count(n);
	cp = n;
	if (n < 0)
		cp = -cp;
	str = malloc(sizeof(char) * (ft_count(n) + 1));
	if (str == NULL)
		return (NULL);
	str[size] = '\0';
	while (cp > 0)
	{
		str[size - 1] = (cp % 10) + '0';
		cp = cp / 10;
		size--;
	}
	if (n == 0)
		str[0] = '0';
	if (n < 0)
		str[0] = '-';
	return (str);
}
