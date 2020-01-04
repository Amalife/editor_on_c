#include "std_n_def.h"
#include "func_pro.h"
#include "global.h"

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
