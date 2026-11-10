#include "libftprintf.h"

void    ft_putunsnbr(unsigned int nb)
{
    char    c;

    if (nb > 9)
        ft_putunsnbr(nb / 10);
    c = (nb % 10) + '0';
    ft_putchar(c);
}