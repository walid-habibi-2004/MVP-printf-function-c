/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_average.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wahabibi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 14:11:42 by wahabibi          #+#    #+#             */
/*   Updated: 2026/11/07 14:23:27 by wahabibi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdarg.h>

double ft_average(int c, ...)
{
	va_list	arg;
	int	i;
	double	sum;
	double	av;

	if (c == 0)
		return (0);
	va_start(arg, c);
	i = 0;
	sum = 0;
	while (i < c)
	{
		sum += va_arg(arg, int);
		i++;
	}
	av = sum / c;
	va_end(arg);
	return (av);
}

int	main(void)
{
	printf("av = %0.0f\n", ft_average(1, 10));
	printf("av = %0.0f\n", ft_average(2, 10, 20));
	printf("av = %0.0f\n", ft_average(3, 10, 20, 30));
	printf("av = %0.0f\n", ft_average(4, 10, 20, 30, 40));
	printf("av = %0.0f\n", ft_average(5, 10, 20, 30, 40, 50));
	printf("av = %0.0f\n", ft_average(5, 1, 2, 3, 4, 5));
	printf("av = %0.0f\n", ft_average(3, -10, 0, 10));
	printf("av = %0.1f\n", ft_average(4, 1, 2, 3, 4));
}
