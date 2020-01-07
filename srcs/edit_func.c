#include "std_n_def.h"
#include "func_pro.h"
#include "global.h"

int     str_num;

int edit_func(t_cmd_list *cmd, t_doub_list *str_list)
{
    char    *new_str = NULL;
    int     k;
    int     pos;
    char    sym;
    char    *buf = NULL;
    t_node  *ptr;

    k = 0;
    ptr = str_list->head;
    if (cmd->num_par != 4)
        return PARAMS_ERR;
    if (strcmp(cmd->params[0], "string"))
        return PARAMS_ERR;
    str_num = ft_atoi(cmd->params[1]);
    if (str_num <= 0 || str_num > str_list->str_count)
        return PARAMS_ERR;
    pos = ft_atoi(cmd->params[2]);
    while (str_num != ptr->num)
        ptr = ptr->next;
    if (pos <= 0 || pos > ptr->width - 1)
        return PARAMS_ERR;
    if (strlen(cmd->params[3]) == 1)
        sym = cmd->params[3][0];
    else if (strlen(cmd->params[3]) == 2 && cmd->params[3][0] == '\\')
    {
        buf = sp_sym_handler(cmd->params[3]);
        if (buf[1] == '\0')
            sym = buf[0];
        else
        {
            cmd->params[3] = buf;
            return SP_SYM_ERR;
        }
    }
    else
        return PARAMS_ERR;
    if (sym == '\n')
    {
        new_str = (char*)malloc(sizeof(char) * (strlen(ptr->str) + 1));
        while (ptr->str[k])
        {
            new_str[k] = ptr->str[k];
            k++;
        }
        new_str[k-1] = '\0';
        new_str[pos-1] = sym;
        delete_node(str_list, str_num);
        str_num--;
        if (add_new_str(str_list, new_str) == LIST_ADD_ERR)
        {
            free(new_str);
            return LIST_ADD_ERR;
        }
        free(new_str);
    }
    else
        ptr->str[pos-1] = sym;
    str_list->flags[F_CHANGED] = 1;
    ft_putstr("string edited\n");
    if (buf)
        cmd->params[3] = buf;
    return 0;
}
