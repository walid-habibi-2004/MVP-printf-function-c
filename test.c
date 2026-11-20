#include <stdio.h>
#include <stdarg.h>

void fonc(int a, ...)
{
    va_list args;

    va_start(args, a);
    printf("%d\n", *(int *)((char *)args->reg_save_area + args->gp_offset));
    args->gp_offset += 8;
    printf("%0.1f\n", *(double *)((char *)args->reg_save_area + args->fp_offset));
    args->fp_offset += 16;
    printf("%s\n", *(char **)((char *)args->reg_save_area + args->gp_offset));
}

int main(void)
{
    fonc(4, 4, 2.2, "hello");
}