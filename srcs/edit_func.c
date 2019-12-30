#include "std_n_def.h"
#include "func_pro.h"
#include "global.h"

int edit_func(char **params, t_doub_list *str_list)
{
    int     str;
    int     pos;
    t_node  *save;
    char    sym;

    if (strcmp(params[0], "string"))
        return PARAMS_ERR;
    if (params[4])
        return PARAMS_ERR;
    if (strlen(params[3]) == 1)
        sym = params[3][0];
    else
        return PARAMS_ERR;
    str = ft_atoi(params[1]);
    if (str <= 0 || str > str_list->str_count)
        return PARAMS_ERR;
    pos = ft_atoi(params[2]);
    save = str_list->head;
    while (str != str_list->head->num)
        str_list->head = str_list->head->next;
    if (pos <= 0 || pos > str_list->head->width)
    {
        str_list->head = save;
        return PARAMS_ERR;
    }
    str_list->head->str[pos-1] = sym;
    str_list->head = save;
    str_list->flags[F_CHANGED] = 1;
    return 0;
}
