/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wahabibi <wahabibi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 16:46:49 by wahabibi          #+#    #+#             */
/*   Updated: 2026/11/12 14:04:45 by wahabibi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static	int	ft_check_format(char format, va_list args)
{
	if (format == 'c')
		return (ft_putchar(va_arg(args, int)));
	else if (format == 'd' || format == 'i')
		return (ft_putnbr(va_arg(args, int)));
	else if (format == 'u')
		return (ft_putunsnbr(va_arg(args, unsigned int)));
	else if (format == 's')
		return (ft_putstr(va_arg(args, char *)));
	else if (format == 'p')
		return (ft_putaddress(va_arg(args, void *)));
	else if (format == 'x')
		return (ft_puthex(va_arg(args, unsigned int), 'x'));
	else if (format == 'X')
		return (ft_puthex(va_arg(args, unsigned int), 'X'));
	else if (format == '%')
		return (ft_putchar('%'));
	return (-1);
}

static	int	ft_process_char(const char *str, int i, va_list args)
{
	int	help;

	if (str[i] == '%')
	{
		if (str[i + 1] == '\0')
			return (-2);
		help = ft_check_format(str[i + 1], args);
		if (help == -1)
			return (-1);
	}
	else
	{
		help = ft_putchar(str[i]);
		if (help == -1)
			return (-1);
	}
	return (help);
}

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
		help = ft_process_char(str, i, args);
		if (help == -2)
			break ;
		else if (help == -1)
		{
			va_end(args);
			return (-1);
		}
		if (str[i] == '%')
			i++;
		len += help;
		i++;
	}
	va_end(args);
	return (len);
}
