/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wahabibi <wahabibi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 16:41:03 by wahabibi          #+#    #+#             */
/*   Updated: 2026/11/11 13:41:47 by wahabibi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_putnbr(int nb)
{
	int		len;
	int		tmp;
	char	c;

	len = 0;
	if (nb == -2147483648)
	{
		if (write(1, "-2147483648", 11) == -1)
			return (-1);
		return (11);
	}
	if (nb < 0)
	{
		if (ft_putchar('-') == -1)
			return (-1);
		nb = -nb;
		len++;
	}
	if (nb > 9)
	{
		tmp = ft_putnbr(nb / 10);
		if (tmp == -1)
			return (-1);
		len += tmp;
	}
	c = (nb % 10) + '0';
	if (ft_putchar(c) == -1)
		return (-1);
	len ++;
	return (len);
}
