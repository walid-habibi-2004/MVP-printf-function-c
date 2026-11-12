/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadresse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wahabibi <wahabibi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/11 18:25:03 by wahabibi          #+#    #+#             */
/*   Updated: 2026/11/12 15:44:15 by wahabibi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>

static	int	ft_check_addr(void)
{
	int	len;
	int	help;

	len = 0;
	help = ft_putstr("(nil)");
	if (help == -1)
		return (-1);
	len += help;
	return (len);
}

static	char	*ft_make_addr(void *addr)
{
	int		i;
	char	*add;
	size_t	n;
	size_t	tmp;

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
		return (NULL);
	add[i] = '\0';
	while (i > 0)
	{
		add[i - 1] = "0123456789abcdef"[tmp % 16];
		tmp /= 16;
		i--;
	}
	return (add);
}

static	int	ft_print_adresse(char *add)
{
	int	len;
	int	help;

	len = 0;
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
	free(add);
	return (len += help);
}

int	ft_putadresse(void *addr)
{
	char	*add;

	if (!addr)
		return (ft_check_addr());
	add = ft_make_addr(addr);
	if (!add)
		return (-1);
	return (ft_print_adresse(add));
}
