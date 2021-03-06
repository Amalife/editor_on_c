#include "std_n_def.h"
#include "func_pro.h"
#include "global.h"

int set_func(t_cmd_list *cmd, t_doub_list *str_list)
{
    if (cmd->num_par < 1 || cmd->num_par > 2)
        return PARAMS_ERR;
    if (strcmp(cmd->params[0], "numbers") == 0 && cmd->num_par == 2)
        if (strcmp(cmd->params[1], "yes") == 0)
        {
            str_list->flags[F_NUM] = 1;
            ft_putstr("Numbers on\n");
        }
        else if (strcmp(cmd->params[1], "no") == 0)
        {
            str_list->flags[F_NUM] = 0;
            ft_putstr("Numbers off\n");
        }
        else
            return PARAMS_ERR;
    else if (strcmp(cmd->params[0], "wrap") == 0 && cmd->num_par == 2)
        if (strcmp(cmd->params[1], "yes") == 0)
        {
            str_list->flags[F_NO_WRAP] = 0;
            ft_putstr("Wrap on\n");
        }
        else if (strcmp(cmd->params[1], "no") == 0)
        {
            str_list->flags[F_NO_WRAP] = 1;
            ft_putstr("Wrap off\n");
        }
        else
            return PARAMS_ERR;
    else if (strcmp(cmd->params[0], "tabwidth") == 0 && cmd->num_par == 2)
    {
        if (ft_atoi(cmd->params[1]) > 0)
        {
            str_list->tab_width = ft_atoi(cmd->params[1]);
            ft_putstr("Tabwidth is ");
            ft_putnbr(str_list->tab_width);
            ft_putchar('\n');
        }
        else 
            return TAB_ERR;
    }
    else if (strcmp(cmd->params[0], "name") == 0)
    {
        if (cmd->num_par == 2)
        {
            if (check_quotes(cmd->params[1]))
            {
                free(str_list->file_link);
                str_list->file_link = unquoting(cmd->params[1]);
            }
            else
                return PARAMS_ERR;
        }
        else
        {
            if (str_list->file_link)
                free(str_list->file_link);
            str_list->file_link = NULL;
        }
        ft_putstr("Name changed\n");
    }
    else
        return PARAMS_ERR;
    return 0;
}
