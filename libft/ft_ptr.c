/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 18:35:13 by zamgar            #+#    #+#             */
/*   Updated: 2024/10/07 18:35:14 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	ft_get_size_ptrarray(unsigned long long adress)
{
	int	i;

	i = 0;
	while (adress >= 1)
	{
		adress = adress / 16;
		i++;
	}
	return (i);
}

char	*ft_fill_ptrarray(unsigned long long adress, char *string, char *array)
{
	int					i;
	unsigned long long	temp;

	i = 0;
	temp = 0;
	while (adress > 0)
	{
		temp = adress % 16;
		array[i] = string[temp];
		i++;
		adress = adress / 16;
	}
	array[i] = '\0';
	return (array);
}

int	ft_putptr(unsigned long long adress)
{
	char				*string;
	char				*array;
	int					i;

	i = 0;
	string = "0123456789abcdef";
	if (adress == 0)
	{
		ft_putstr("(nil)");
		return (5);
	}
	ft_putstr("0x");
	array = (char *)malloc(sizeof(char) * ft_get_size_ptrarray(adress) + 1);
	if (array == NULL)
		return (0);
	array = ft_fill_ptrarray(adress, string, array);
	i = ft_strlen(array);
	ft_print_array(array, i - 1);
	free(array);
	return (i + 2);
}
