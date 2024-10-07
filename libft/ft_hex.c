/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:34:47 by zamgar            #+#    #+#             */
/*   Updated: 2024/10/07 18:34:48 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	ft_get_size_hexarray(unsigned int n)
{
	int	i;

	i = 0;
	while (n >= 1)
	{
		n = n / 16;
		i++;
	}
	return (i);
}

char	*ft_fill_hexarray(unsigned int n, char *string, char *array)
{
	int				i;
	unsigned int	temp;

	i = 0;
	temp = 0;
	while (n > 0)
	{
		temp = n % 16;
		array[i] = string[temp];
		i++;
		n = n / 16;
	}
	array[i] = '\0';
	return (array);
}

void	ft_print_array(char *array, int i)
{
	while (i >= 0)
	{
		ft_putchar(array[i]);
		i--;
	}
}

int	ft_dec_into_hex(unsigned int n, int b)
{
	char			*string;
	char			*array;
	int				i;

	i = 0;
	if (b == 1)
		string = "0123456789ABCDEF";
	if (b == 0)
		string = "0123456789abcdef";
	if (n == 0)
	{
		ft_putchar('0');
		return (1);
	}
	array = (char *)malloc(sizeof(char) * ft_get_size_hexarray(n) + 1);
	if (array == NULL)
		return (0);
	array = ft_fill_hexarray(n, string, array);
	i = ft_strlen(array);
	ft_print_array(array, i - 1);
	free(array);
	return (i);
}
