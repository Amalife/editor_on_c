#include "std_n_def.h"
#include "func_pro.h"
#include "global.h"

int edit_func(t_cmd_list *cmd, t_doub_list *str_list)
{
    int     str;
    int     pos;
    t_node  *save;
    char    sym;

    if (cmd->num_par != 4)
        return PARAMS_ERR;
    if (strcmp(cmd->params[0], "string"))
        return PARAMS_ERR;
    if (strlen(cmd->params[3]) == 1)
        sym = cmd->params[3][0];
    else
        return PARAMS_ERR;
    str = ft_atoi(cmd->params[1]);
    if (str <= 0 || str > str_list->str_count)
        return PARAMS_ERR;
    pos = ft_atoi(cmd->params[2]);
    save = str_list->head;
    while (str != str_list->head->num)
        str_list->head = str_list->head->next;
    if (pos <= 0 || pos > str_list->head->width - 1)
    {
        str_list->head = save;
        return PARAMS_ERR;
    }
    str_list->head->str[pos-1] = sym;
    str_list->head = save;
    str_list->flags[F_CHANGED] = 1;
    ft_putstr("string edited\n");
    return 0;
}
