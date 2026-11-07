/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wahabibi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 16:46:49 by wahabibi          #+#    #+#             */
/*   Updated: 2026/11/07 17:19:14 by wahabibi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

void	ft_putchar(char c);
void	ft_putnbr(int nb);
void	ft_putstr(char *str);

void	ft_printf(const char *str, ...)
{
	va_list	args;
	int	i;

	va_start(args, str);
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			if (str[i + 1] == 'd')
				ft_putnbr(va_arg(args, int));
			else if (str[i + 1] == 'c')
				ft_putchar(va_arg(args, int));
			else if (str[i + 1] == 's')
				ft_putstr(va_arg(args, char *));
			i++;
		}
		else
			ft_putchar(str[i]);
		i++;
	}
	va_end(args);
}

int	main(void)
{
	ft_printf("my name is: %s and my age is: %d and my gropage is: %c\n","walid", 42, 'B');
}
