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
        write(STDOUT_FILENO, str, sizeof(char));
        str++;
    }
}

int ft_atoi(char *str)
{
    int sign;
    int nb;
    int i;

    sign = 1;
    nb = 0;
    i = 0;
    if (str[i] == '-')
    {
        sign = -1;
        i++;
    }
    else if (str[i] == '+')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
    {
        nb = (nb * 10) + (str[i] - '0');
        i++;
    }
    if (str[i])
        return -1;
    return (sign * nb);
}
