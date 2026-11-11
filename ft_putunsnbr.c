#include "libftprintf.h"

int    ft_putunsnbr(unsigned int nb)
{
    char    c;
    int     len;

    len = 0;
    if (nb > 9)
        len += ft_putunsnbr(nb / 10);
    c = (nb % 10) + '0';
    len += ft_putchar(c);
    return (len);
}