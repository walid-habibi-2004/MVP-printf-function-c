#include "libftprintf.h"
#include <stdio.h>

void    ft_putaddress(void *addr)
{
    size_t  n;
    size_t  tmp;
    char    *add;
    int     i;

    n = (size_t)addr;
    tmp = n;
    i = 0;
    while (n > 0)
    {
        n /= 16;
        i++;
    }
    add = malloc((i + 1) * sizeof(char));
    if (!add)
        return ;
    add[i] = '\0';
    while (i > 0)
    {
        add[i - 1] = "0123456789abcdef"[tmp % 16];
        tmp /= 16;
        i--;
    }
    ft_putstr("0x");
    ft_putstr(add);
    free(add);
}