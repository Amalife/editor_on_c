#include "std_n_def.h"
#include "func_pro.h"

void    ft_putchar(char c)
{
    write(STDOUT_FILENO, &c, sizeof(char));
}

void    ft_putstr(char *str)
{
    while (*str)
    {
        ft_putchar(*str);
        str++;
    }
}
