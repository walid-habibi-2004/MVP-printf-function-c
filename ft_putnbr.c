/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wahabibi <wahabibi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 16:41:03 by wahabibi          #+#    #+#             */
/*   Updated: 2026/11/10 18:43:19 by wahabibi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_putnbr(int nb)
{
	int		len;
	char	c;

	len = 0;
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
		len++;
	}
	if (nb > 9)
		len += ft_putnbr(nb / 10);
	c = (nb % 10) + '0';
	len += ft_putchar(c);
	return (len);
}
