/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wahabibi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 13:53:03 by wahabibi          #+#    #+#             */
/*   Updated: 2026/11/07 14:18:47 by wahabibi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>

int	ft_max(int c, ...)
{
	va_list	arg;
	int	i;
	int	max;
	int	max_x;

	if (c == 0)
		return (0);
	va_start(arg, c);
	i = 0;
	max = va_arg(arg, int);
	max_x = 0;
	while (i < c - 1)
	{
		max_x = va_arg(arg, int);
		if (max < max_x)
			max  = max_x;
		i++;
	}
	va_end(arg);
	return (max);
}

int	main(void)
{
	printf("max = %d\n", ft_max(7, 9, 0, 12, 3, 55, 1007, 1000));
	return (0);
}
