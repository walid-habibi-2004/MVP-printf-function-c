/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sum.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wahabibi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 12:09:39 by wahabibi          #+#    #+#             */
/*   Updated: 2026/11/07 12:30:50 by wahabibi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>

int	ft_sum(int count, ...)
{
	va_list	args;
	int	i;
	int	r;

	i = 0;
	r = 0;
	va_start(args, count);
	while (i < count)
	{
		r += va_arg(args, int);
		i++;
	}
	va_end(args);
	return (r);
}

int	main(void)
{
	printf("sum = %d\n", ft_sum(3, 10, 20, 30));
	return (0);
}
