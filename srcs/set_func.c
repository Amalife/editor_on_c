#include "std_n_def.h"
#include "func_pro.h"
#include "global.h"

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

int set_func(char **params, t_doub_list *str_list)
{
    if (strcmp(params[0], "numbers") == 0)
        if (strcmp(params[1], "yes") == 0)
        {
            str_list->flags[F_NUM] = 1;
            ft_putstr("Numbers on\n");
        }
        else if (strcmp(params[1], "no") == 0)
        {
            str_list->flags[F_NUM] = 0;
            ft_putstr("Numbers off\n");
        }
        else
            return PARAMS_ERR;
    else if (strcmp(params[0], "wrap") == 0)
        if (strcmp(params[1], "yes") == 0)
        {
            str_list->flags[F_NO_WRAP] = 0;
            ft_putstr("Wrap on\n");
        }
        else if (strcmp(params[1], "no") == 0)
        {
            str_list->flags[F_NO_WRAP] = 1;
            ft_putstr("Wrap off\n");
        }
        else
            return PARAMS_ERR;
    else if (strcmp(params[0], "tabwidth") == 0 && params[1])
    {
        if (ft_atoi(params[1]) > 0)
        {
            str_list->tab_width = ft_atoi(params[1]);
            ft_putstr("Tabwidth is ");
            ft_putnbr(str_list->tab_width);
            ft_putchar('\n');
        }
        else 
            return TAB_ERR;
    }
    else
        return PARAMS_ERR;
    return 0;
}
