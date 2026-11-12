/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wahabibi <wahabibi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 16:46:49 by wahabibi          #+#    #+#             */
/*   Updated: 2026/11/11 18:20:43 by wahabibi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;
	int		help;
	int		i;

	va_start(args, str);
	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == '\0')
				break ;
			if (str[i + 1] == 'd' || str[i + 1] == 'i')
			{
				help = ft_putnbr(va_arg(args, int));
				if (help == -1)
				{
					va_end(args);
					return (-1);
				}
				len += help;
			}
			else if (str[i + 1] == 'c')
			{
				help = ft_putchar(va_arg(args, int));
				if (help == -1)
				{
					va_end(args);
					return (-1);
				}
				len += help;
			}
			else if (str[i + 1] == 's')
			{
				help = ft_putstr(va_arg(args, char *));
				if (help == -1)
				{
					va_end(args);
					return (-1);
				}
				len += help;
			}
			else if (str[i + 1] == 'u')
			{
				help = ft_putunsnbr(va_arg(args, unsigned int));
				if (help == -1)
				{
					va_end(args);
					return (-1);
				}
				len += help;
			}
			else if (str[i + 1] == 'p')
			{
				help = ft_putaddress(va_arg(args, void *));
				if (help == -1)
				{
					va_end(args);
					return (-1);
				}
				len += help;
			}
			else if (str[i + 1] == 'x')
			{
				help = ft_puthex(va_arg(args, unsigned int), 'x');
				if (help == -1)
				{
					va_end(args);
					return (-1);
				}
				len += help;
			}
			else if (str[i + 1] == 'X')
			{
				help = ft_puthex(va_arg(args, unsigned int), 'X');
				if (help == -1)
				{
					va_end(args);
					return (-1);
				}
				len += help;
			}
			else if (str[i + 1] == '%')
			{
				help = ft_putchar('%');
				if (help == -1)
				{
					va_end(args);
					return (-1);
				}
				len += help;
			}
			i++;
		}
		else
		{
			help = ft_putchar(str[i]);
			if (help == -1)
			{
				va_end(args);
				return (-1);
			}
			len += help;
		}
		i++;
	}
	va_end(args);
	return (len);
}
