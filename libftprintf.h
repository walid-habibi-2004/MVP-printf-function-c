/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wahabibi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 15:50:20 by wahabibi          #+#    #+#             */
/*   Updated: 2026/11/12 15:52:33 by wahabibi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

int	ft_printf(const char *str, ...);
int	ft_putnbr(int nb);
int	ft_putstr(char *str);
int	ft_putchar(char c);
int	ft_puthex(unsigned int nb, char x);
int	ft_putunsnbr(unsigned int nb);
int	ft_putadresse(void *addr);

#endif
