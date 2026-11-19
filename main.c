#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>

int	main(void)
{
	int		a;
	int		b;
	int		n;
	char	*str;

	str = "Walid";

	printf("\n===== CHAR =====\n");
	a = printf("[%c] [%c]\n", 'A', 'Z');
	b = ft_printf("[%c] [%c]\n", 'A', 'Z');
	printf("Return: %d / %d\n", a, b);

	printf("\n===== STRING =====\n");
	a = printf("[%s] [%s] [%s]\n", str, "", (char *)NULL);
	b = ft_printf("[%s] [%s] [%s]\n", str, "", (char *)NULL);
	printf("Return: %d / %d\n", a, b);

	printf("\n===== POINTER =====\n");
	n = 42;
	a = printf("[%p] [%p]\n", &n, NULL);
	b = ft_printf("[%p] [%p]\n", &n, NULL);
	printf("Return: %d / %d\n", a, b);

	printf("\n===== DECIMAL =====\n");
	a = printf("[%d] [%i] [%d]\n", 0, -42, INT_MAX);
	b = ft_printf("[%d] [%i] [%d]\n", 0, -42, INT_MAX);
	printf("Return: %d / %d\n", a, b);

	printf("\n===== INT MIN =====\n");
	a = printf("[%d]\n", INT_MIN);
	b = ft_printf("[%d]\n", INT_MIN);
	printf("Return: %d / %d\n", a, b);

	printf("\n===== UNSIGNED =====\n");
	a = printf("[%u] [%u]\n", 0, UINT_MAX);
	b = ft_printf("[%u] [%u]\n", 0, UINT_MAX);
	printf("Return: %d / %d\n", a, b);

	printf("\n===== HEX =====\n");
	a = printf("[%x] [%X]\n", 255, UINT_MAX);
	b = ft_printf("[%x] [%X]\n", 255, UINT_MAX);
	printf("Return: %d / %d\n", a, b);

	printf("\n===== PERCENT =====\n");
	a = printf("[%%] [%%] [%]\n");
	b = ft_printf("[%%] [%%] [%]\n");
	printf("Return: %d / %d\n", a, b);

	printf("\n===== MIXED =====\n");
	a = printf("%c %s %d %i %u %x %X %%\n",
			'W', "Walid", -42, 42, UINT_MAX, 255, 255);
	b = ft_printf("%c %s %d %i %u %x %X %%\n",
			'W', "Walid", -42, 42, UINT_MAX, 255, 255);
	printf("Return: %d / %d\n", a, b);

	printf("\n===== NULL FORMAT =====\n");
    a = printf(NULL);
	b = ft_printf(NULL);
	printf("Return: %d / %d\n", a, b);

	printf("\n===== EMPTY STRING =====\n");
	a = printf("");
	b = ft_printf("");
	printf("Return: %d / %d\n", a, b);

	printf("\n===== LONG STRING =====\n");
	a = printf("This is a long string to test the return value.\n");
	b = ft_printf("This is a long string to test the return value.\n");
	printf("Return: %d / %d\n", a, b);

	return (0);
}

// int main()
// {
//     int a = printf("%[]\n");
//     int b = ft_printf("%[]\n");
//     printf("a = %d \nb = %d \n", a, b);
// }

// int main(void)
// {
//     int a = ft_printf(NULL);
//     int b = printf(NULL);
//     printf("b = %d\n", b);
//     printf("a = %d\n", a);
//     return (0);
// }