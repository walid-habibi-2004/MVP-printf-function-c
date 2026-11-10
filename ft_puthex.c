#include "libftprintf.h"

static void    ft_print_hex(unsigned int nb, char x)
{
    // char    *he_x;

    if (nb == 0)
        return ;

    // he_x = "0123456789abcdef";
    if (nb > 0)
    {
        ft_print_hex(nb / 16, x);
        if (x == 'x')
            ft_putchar("0123456789abcdef"[nb % 16]);
        else if (x == 'X')
            ft_putchar("0123456789ABCDEF"[nb % 16]);
        nb /= 16;
    }
}

void    ft_puthex(unsigned int nb, char x)
{
    if (nb == 0)
    {
        ft_putchar('0');
        return ;
    }
    else
        ft_print_hex(nb, x);
}