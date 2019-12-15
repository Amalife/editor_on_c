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

int     ft_space(char *str, int k)
{
    while (str[k] == ' ' || str[k] == '\t')
        k++;
    return k;
}

int     ft_strlen(char *str)
{
    int n;

    n = 0;
    while (*str)
    {
        n++;
        str++;
    }
    return n;
}
