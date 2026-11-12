/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wahabibi <wahabibi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 16:41:03 by wahabibi          #+#    #+#             */
/*   Updated: 2026/11/12 14:20:10 by wahabibi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static	int	ft_putmin(void)
{
	if (write(1, "-2147483648", 11) == -1)
		return (-1);
	return (11);
}

int	ft_putnbr(int nb)
{
	int		len;
	int		tmp;

	len = 0;
	if (nb == -2147483648)
		return (ft_putmin());
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
	if (ft_putchar((nb % 10) + '0') == -1)
		return (-1);
	len ++;
	return (len);
}
