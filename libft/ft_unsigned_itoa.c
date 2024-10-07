/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_itoa.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:35:27 by zamgar            #+#    #+#             */
/*   Updated: 2024/10/07 18:35:28 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	ft_unsigned_count(unsigned int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_unsigned_itoa(unsigned int n)
{
	int		i;
	char	*str;

	i = ft_unsigned_count(n);
	str = (char *)malloc(sizeof(char) * i + 1);
	if (str == NULL)
		return (NULL);
	if (n == 0)
		str[0] = '0';
	str[i] = '\0';
	while (n >= 10)
	{
		str[i - 1] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	str[i - 1] = n + '0';
	return (str);
}

int	ft_unsigned_itoa2(unsigned int n)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_unsigned_itoa(n);
	i = ft_strlen((const char *)str);
	ft_putstr(str);
	free(str);
	return (i);
}
