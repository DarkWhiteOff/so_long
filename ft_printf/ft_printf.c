/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:48:28 by zamgar            #+#    #+#             */
/*   Updated: 2024/06/13 17:37:42 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	get_next_arg(va_list *ap, char c)
{
	int	printed_lenght;

	printed_lenght = 0;
	if (c == 'c')
		printed_lenght += ft_putchar((va_arg(*ap, int)));
	else if (c == 's')
		printed_lenght += ft_putstr(va_arg(*ap, char *));
	else if (c == 'p')
		printed_lenght += ft_putptr(va_arg(*ap, unsigned long long));
	else if (c == 'd' || c == 'i')
		printed_lenght += ft_itoa2(va_arg(*ap, int));
	else if (c == 'u')
		printed_lenght += ft_unsigned_itoa2(va_arg(*ap, unsigned int));
	else if (c == 'x')
		printed_lenght += ft_dec_into_hex(va_arg(*ap, unsigned int), 0);
	else if (c == 'X')
		printed_lenght += ft_dec_into_hex(va_arg(*ap, unsigned int), 1);
	else if (c == '%')
		printed_lenght += ft_putchar(c);
	return (printed_lenght);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		count;
	va_list	ap;

	i = 0;
	count = 0;
	va_start(ap, str);
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			count += get_next_arg(&ap, str[i + 1]);
			i++;
		}
		else
		{
			ft_putchar(str[i]);
			count++;
		}
		i++;
	}
	return (count);
}
