/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wahabibi <wahabibi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 15:50:20 by wahabibi          #+#    #+#             */
/*   Updated: 2026/11/12 15:58:52 by wahabibi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

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
