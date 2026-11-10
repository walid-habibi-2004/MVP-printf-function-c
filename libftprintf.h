#ifndef LIBFTPRINTF_H
#define LIBFTPRINTF_H

#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

void    ft_printf(const char *, ...);
void    ft_putnbr(int nb);
void    ft_putstr(char *str);
void    ft_putchar(char c);
void    ft_puthex(unsigned int nb, char x);
void    ft_putunsnbr(unsigned int nb);
void    ft_putaddress(void *addr);

#endif