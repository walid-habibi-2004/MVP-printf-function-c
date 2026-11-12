/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wahabibi <wahabibi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 14:31:49 by wahabibi          #+#    #+#             */
/*   Updated: 2026/11/12 15:58:04 by wahabibi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	ft_get_hex(unsigned int nb, char x)
{
	if (x == 'x')
	{
		if (ft_putchar("0123456789abcdef"[nb % 16]) == -1)
			return (-1);
	}
	else if (x == 'X')
	{
		if (ft_putchar("0123456789ABCDEF"[nb % 16]) == -1)
			return (-1);
	}
	return (1);
}

static	int	ft_print_hex(unsigned int nb, char x)
{
	int	len;
	int	tmp;

	if (nb == 0)
		return (0);
	len = 0;
	if (nb > 0)
	{
		tmp = ft_print_hex(nb / 16, x);
		if (tmp == -1)
			return (-1);
		if (ft_get_hex(nb, x) == -1)
			return (-1);
		tmp++;
		len += tmp;
	}
	return (len);
}

int	ft_puthex(unsigned int nb, char x)
{
	int	len;
	int	tmp;

	len = 0;
	if (nb == 0)
	{
		if (ft_putchar('0') == -1)
			return (-1);
		return (1);
	}
	else
	{
		tmp = ft_print_hex(nb, x);
		if (tmp == -1)
			return (-1);
		len += tmp;
	}
	return (len);
}
