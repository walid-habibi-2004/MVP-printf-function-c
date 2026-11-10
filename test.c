#include "libftprintf.h"
#include <stdio.h>
#include <fcntl.h>
// int	main(void)
// {
//     printf("%%% | %%%% | n = %d | s = %s | %%%%% | c = %c\n", 42, "walid", 'c');
//     ft_printf("%%% | %%%% | n = %d | s = %s | %%%%% | c = %c\n", 42, "walid", 'c');
//     printf("\nhex = %X || hex = %x\n", 42, 255);
//     ft_printf("hex = %X || hex = %x\n", 42, 255);
// }


// int	main(void)
// {
//     printf("| %% | n = %d | s = %s || c = %c\n", 42, "walid", 'c');
//     ft_printf("| %% | n = %d | s = %s || c = %c\n", 42, "walid", 'c');
//     printf("\nhex = %X || hex = %x\n", 42, 255);
//     ft_printf("hex = %X || hex = %x\n", 42, 255);
// }

// int main(void)
// {
//     printf("%s |%| %c |%%| %u |%%%| %d |%%%%| %i\n", "walid", 'c', -220, -220, -220);
//     ft_printf("%s |%| %c |%%| %u |%%%| %d |%%%%| %i\n", "walid", 'c', -220, -220, -220);
//     // ft_putunsnbr(0);
//     // ft_printf("\n");
// }

// int main(void)
// {
//     char    c = 42;
//     printf("%p\n", &c);
//     ft_printf("%p\n", &c);
//     return (0);
// }

int main(void)
{
    pclose(stdout);
    int a = printf("%d", 1000);
    int b = ("%d", 1000);
}