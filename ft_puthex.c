#include "libftprintf.h"

static int    ft_print_hex(unsigned int nb, char x)
{
    int     len;

    if (nb == 0)
        return (0);

    len = 0;
    if (nb > 0)
    {
        len += ft_print_hex(nb / 16, x);
        if (x == 'x')
            ft_putchar("0123456789abcdef"[nb % 16]);
        else if (x == 'X')
            ft_putchar("0123456789ABCDEF"[nb % 16]);
        len++;
        // nb /= 16;
    }
    return (len);
}

int    ft_puthex(unsigned int nb, char x)
{
    int     len;

    if (nb == 0)
    {
        ft_putchar('0');
        return (1);
    }
    else
        len = ft_print_hex(nb, x);
    return (len);
}