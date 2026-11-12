/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsnbr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wahabibi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 18:23:59 by wahabibi          #+#    #+#             */
/*   Updated: 2026/11/11 18:24:07 by wahabibi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int	ft_putunsnbr(unsigned int nb)
{
	int		tmp;
	int		len;
	char	c;

	len = 0;
	if (nb > 9)
	{
		tmp = ft_putunsnbr(nb / 10);
		if (tmp == -1)
			return (-1);
		len += tmp;
	}
	c = (nb % 10) + '0';
	if (ft_putchar(c) == -1)
		return (-1);
	len++;
	return (len);
}
