#ifndef LIBFTPRINTF_H
#define LIBFTPRINTF_H

#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>

int    ft_printf(const char *, ...);
int    ft_putnbr(int nb);
int    ft_putstr(char *str);
int    ft_putchar(char c);
int    ft_puthex(unsigned int nb, char x);
int    ft_putunsnbr(unsigned int nb);
int    ft_putadresse(void *addr);

#endif