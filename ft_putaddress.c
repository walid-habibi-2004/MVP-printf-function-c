/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putaddress.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wahabibi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 18:25:03 by wahabibi          #+#    #+#             */
/*   Updated: 2026/11/12 09:58:29 by wahabibi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>

int	ft_putaddress(void *addr)
{
	char		*add;
	size_t	n;
	size_t	tmp;
	int	i;
	int	len;
	int	help;

	len = 0;
	if (!addr)
	{
		help = ft_putstr("(nil)");
		if (help == -1)
			return (-1);
		len += help;
		return (len);
	}
	n = (size_t)addr;
	tmp = n;
	i = 0;
	while (n > 0)
	{
		n /= 16;
		i++;
	}
	add = malloc((i + 1) * sizeof(char));
	if (!add)
		return (-1);
	add[i] = '\0';
	while (i > 0)
	{
		add[i - 1] = "0123456789abcdef"[tmp % 16];
		tmp /= 16;
		i--;
	}
	help = ft_putstr("0x");
	if (help == -1)
	{
		free(add);
		return (-1);
	}
	len += help;
	help = ft_putstr(add);
	if (help == -1)
	{
	    free(add);
	    return (-1);
	}
	len += help;
	free(add);
	return (len);
}
