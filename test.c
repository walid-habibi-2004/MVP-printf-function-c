#include "ft_printf.h"
#include <stdio.h>


#include <stdio.h>
#include <limits.h>

int	main(void)
{
	int	ret1;
	int	ret2;

	printf("===== INT_MIN =====\n");
	ret1 = printf("%d\n", INT_MIN);
	ret2 = ft_printf("%d\n", INT_MIN);
	printf("Return: printf = %d | ft_printf = %d\n\n", ret1, ret2);

	printf("===== INT_MAX =====\n");
	ret1 = printf("%d\n", INT_MAX);
	ret2 = ft_printf("%d\n", INT_MAX);
	printf("Return: printf = %d | ft_printf = %d\n\n", ret1, ret2);

	printf("===== UINT_MAX =====\n");
	ret1 = printf("%u\n", UINT_MAX);
	ret2 = ft_printf("%u\n", UINT_MAX);
	printf("Return: printf = %d | ft_printf = %d\n\n", ret1, ret2);

	printf("===== ZERO =====\n");
	ret1 = printf("%d %u %x %X\n", 0, 0, 0, 0);
	ret2 = ft_printf("%d %u %x %X\n", 0, 0, 0, 0);
	printf("Return: printf = %d | ft_printf = %d\n\n", ret1, ret2);

	printf("===== HEX =====\n");
	ret1 = printf("%x %X\n", UINT_MAX, UINT_MAX);
	ret2 = ft_printf("%x %X\n", UINT_MAX, UINT_MAX);
	printf("Return: printf = %d | ft_printf = %d\n\n", ret1, ret2);

	printf("===== POINTER =====\n");
	int	n = 42;
	ret1 = printf("%p %p\n", &n, NULL);
	ret2 = ft_printf("%p %p\n", &n, NULL);
	printf("Return: printf = %d | ft_printf = %d\n\n", ret1, ret2);

	return (0);
}
