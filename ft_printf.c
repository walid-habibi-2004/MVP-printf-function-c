/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wahabibi <wahabibi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 16:46:49 by wahabibi          #+#    #+#             */
/*   Updated: 2026/11/10 18:52:40 by wahabibi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_printf(const char *str, ...)
{
	int		len;
	va_list	args;
	int	i;

	va_start(args, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == 'd' || str[i + 1] == 'i')
				len += ft_putnbr(va_arg(args, int));
			else if (str[i + 1] == 'c')
				len += ft_putchar(va_arg(args, int));
			else if (str[i + 1] == 's')
				len += ft_putstr(va_arg(args, char *));
			else if (str[i + 1] == 'u')
				len += ft_putunsnbr(va_arg(args, unsigned int));
			else if (str[i + 1] == 'p')
				len += ft_putaddress(va_arg(args, void *));
			else if (str[i + 1] == 'x')
				len += ft_puthex(va_arg(args, unsigned int), 'x');
			else if (str[i + 1] == 'X')
				len += ft_puthex(va_arg(args, unsigned int), 'X');
			else if (str[i + 1] == '%')
				ft_putchar('%');
			else
			{
				ft_putchar('%');
				ft_putchar(str[i + 1]);
			}
			i++;
		}
		else
		{
			ft_putchar(str[i]);
			len++;
		}
		i++;
	}
	va_end(args);
	return (len);
}


