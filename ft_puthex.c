#include "libftprintf.h"

static int    ft_print_hex(unsigned int nb, char x)
{
    int     len;
    int     tmp;

    if (nb == 0)
        return (0);

    len = 0;
    if (nb > 0)
    {
        tmp = ft_print_hex(nb / 16, x);
        if (tmp == -1)
            return (-1);
        if (x == 'x')
        {
            if (ft_putchar("0123456789abcdef"[nb % 16]) == -1)
                return (-1);
            len++;
        }
        else if (x == 'X')
        {
            if (ft_putchar("0123456789ABCDEF"[nb % 16]) == -1)
                return (-1);
            len++;
        }
        len += tmp;
    }
    return (len);
}

int    ft_puthex(unsigned int nb, char x)
{
    int     len;
    int     tmp;

    len = 0;
    if (nb == 0)
    {
        if (ft_putchar('0') == -1)
            return (-1);
        return (1);
    }
    else
    {
        tmp = ft_print_hex(nb, x);
        if (tmp == -1)
            return (-1);
        len += tmp;
    }
    return (len);
}