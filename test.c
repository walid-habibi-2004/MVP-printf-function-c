#include "libftprintf.h"
#include <stdio.h>
#include <fcntl.h>

// int	main(void)
// {
//     // printf("%%% | %%%% | n = %d | s = %s | %%%%% | c = %c\n", 42, "walid", 'c');
//     // ft_printf("%%% | %%%% | || %%%%% |||%");
//     printf("walid %");
//     // printf("\nhex = %X || hex = %x\n", 42, 255);
//     // ft_printf("hex = %X || hex = %x\n", 42, 255);
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

// int main(void)
// {
//     pclose(stdout);
//     int a = printf("%d", 1000);
//     int b = ("%d", 1000);
// }


// return value test:

// int main(void)
// {
//     int y = printf("my name is = %s || %c\n", "walid", 'c');
//     int x = ft_printf("my name is = %s || \n", "walid", 'c');
//     printf("y = %d || x = %d\n", y, x);
//     return (0);
//}

// int main(void)
// {
//     int c = 42;
//     int y = printf("hex = %x || %X\n", 0, 42);
//     int x = ft_printf("hex = %x || %X\n", 0, 42);
//     printf("y = %d || x = %d\n", y, x);
//     return (0);
// }

// int main(void)
// {
//     int y = printf("d = %u\n", 123456);
//     int x = ft_printf("d = %u\n", 123456);
//     printf("y = %d || x = %d\n", y, x);
//     return (0);
// }

// int main(void)
// {
//     int y = printf("d = %d\n", -21);
//     int x = ft_printf("d = %d\n", -21);
//     printf("y = %d || x = %d\n", y, x);
//     return (0);
// }

// int main(void)
// {
//     int c = 42;
//     int y = printf("%d %i %u %c %s %x %X %p\n", 11, -12, 123456789, 'c', (char *)NULL, 0, -42, NULL);
//     int x = ft_printf("%d %i %u %c %s %x %X %p\n", 11, -12, 123456789, 'c', NULL, 0, -42, NULL);
//     printf("y = %d || x = %d\n", y, x);
//     return (0);
// }