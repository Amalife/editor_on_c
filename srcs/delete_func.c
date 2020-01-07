#include "std_n_def.h"
#include "func_pro.h"
#include "global.h"

void    delete_node(t_doub_list *str_list, int str_num)
{
    t_node  *save_tail = NULL;
    t_node  *ptr;

    ptr = str_list->head;
    while (ptr->num != str_num)
        ptr = ptr->next;
    free(ptr->str);
    if (ptr->next == NULL && ptr->prev == NULL)
    {
        free(ptr);
        str_list->head = NULL;
        str_list->tail = NULL;
        str_list->str_count--;
    }
    else if (ptr->next == NULL)
    {
        str_list->tail = ptr->prev;
        ptr->prev->next = NULL;
        free(ptr);
        str_list->str_count--;
    }
    else if (ptr->prev == NULL)
    {
        str_list->head = str_list->head->next;
        ptr->next->prev = NULL;
        free(ptr);
        //save = str_list->head;
        str_list->str_count--;
        save_tail = str_list->tail;
        while (str_list->tail->num != str_num + 1)
        {
            str_list->tail->num--;
            str_list->tail = str_list->tail->prev;
        }
        str_list->tail->num--;
        str_list->tail = save_tail;
    }
    else
    {
        ptr->next->prev = ptr->prev;
        ptr->prev->next = ptr->next;
        free(ptr);
        str_list->str_count--;
        save_tail = str_list->tail;
        while (str_list->tail->num != str_num - 1)
        {
            str_list->tail->num--;
            str_list->tail = str_list->tail->prev;
        }
        str_list->tail = save_tail;
    }
}

int     delete_func(t_cmd_list *cmd, t_doub_list *str_list)
{
    int     rng;
    t_node  *ptr;

    if (str_list->flags[F_FILE] == 0)
        return NO_FILE_ERR;
    if (cmd->num_par < 2 || cmd->num_par > 3)
        return PARAMS_ERR;
    ptr = str_list->head;
    if (strcmp(cmd->params[0], "range") == 0)
    {
        if (cmd->num_par == 3 && ft_atoi(cmd->params[1]) > 0)
        {
            if (ft_atoi(cmd->params[1]) > ft_atoi(cmd->params[2]))
                return PARAMS_ERR;
            if (ft_atoi(cmd->params[1]) > str_list->str_count || 
                                ft_atoi(cmd->params[2]) > str_list->str_count)
                return STR_COUNT_ERR;
            rng = ft_atoi(cmd->params[1]);
            while (rng != ptr->num)
                ptr = ptr->next;
            rng = ft_atoi(cmd->params[2]);
            rng -= ft_atoi(cmd->params[1]);
            rng++;
        }
        else if (cmd->num_par == 2)
        {
            if (ft_atoi(cmd->params[1]) <= 0)
                return PARAMS_ERR;
            rng = ft_atoi(cmd->params[1]);
            if (rng > str_list->str_count)
                return PARAMS_ERR;
            while (rng != ptr->num)
                ptr = ptr->next;
            rng = str_list->str_count - rng + 1;
        }
        else
            return PARAMS_ERR;
    }
    else
        return PARAMS_ERR;
    while (rng)
    {
        if (ptr->next)
        {
            ptr = ptr->next;
            delete_node(str_list, ptr->prev->num);
        }
        else
            delete_node(str_list, ptr->num);
        rng--;
    }
    ft_putstr("String deleted\n");
    str_list->flags[F_CHANGED] = 1;
    //if (str_list->head)
      //  str_list->head = save;
    return 0;
}
