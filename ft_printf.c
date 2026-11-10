/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wahabibi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 16:46:49 by wahabibi          #+#    #+#             */
/*   Updated: 2026/11/07 17:19:14 by wahabibi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	ft_printf(const char *str, ...)
{
	va_list	args;
	int	i;

	va_start(args, str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == 'd' || str[i + 1] == 'i')
				ft_putnbr(va_arg(args, int));
			else if (str[i + 1] == 'c')
				ft_putchar(va_arg(args, int));
			else if (str[i + 1] == 's')
				ft_putstr(va_arg(args, char *));
			else if (str[i + 1] == 'u')
				ft_putunsnbr(va_arg(args, unsigned int));
			else if (str[i + 1] == 'p')
				ft_putaddress(va_arg(args, void *));
			else if (str[i + 1] == 'x')
				ft_puthex(va_arg(args, unsigned int), 'x');
			else if (str[i + 1] == 'X')
				ft_puthex(va_arg(args, unsigned int), 'X');
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
			ft_putchar(str[i]);
		i++;
	}
	va_end(args);
}


