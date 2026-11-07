/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wahabibi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/07 14:29:03 by wahabibi          #+#    #+#             */
/*   Updated: 2026/11/07 15:26:36 by wahabibi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

void	ft_putnbr(int nb)
{
	char	c;

	if (nb == -2147483648)
	{
		ft_putstr("-2147483648");
		return ;
	}
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (nb > 9)
		ft_putnbr(nb / 10);
	c = (nb % 10) + '0';
	ft_putchar(c);
}

void	ft_print(int forma, ...)
{
	va_list	arg;

	va_start(arg, forma);
	if (forma == 'i')
		ft_putnbr(va_arg(arg, int));
	else if (forma == 'c')
		ft_putchar(va_arg(arg, int));
	else if (forma == 's')
		ft_putstr(va_arg(arg, char *));
	else
	{
		va_end(arg);
		return ;
	}
	va_end(arg);
}

int	main(void)
{
	ft_print('i', 42);
	ft_print('c', '\n');
	ft_print('c', 'c');
	ft_print('c', '\n');
	ft_print('s', "hello world\n");
	return (0);
}
