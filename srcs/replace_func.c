#include "std_n_def.h"
#include "func_pro.h"
#include "global.h"

int str_num;
t_node  *ptr;

char    *ft_strcat(char *dest, char *app)
{
    char    *buf;
    int     k;
    int     b;

    k = 0;
    b = 0;
    buf = (char*)malloc(sizeof(char) * (strlen(dest) + strlen(app) + 1));
    while (dest[k])
    {
        buf[b] = dest[k];
        b++;
        k++;
    }
    if (buf[b-1] == '\n')
        b--;
    k = 0;
    while (app[k])
    {
        buf[b] = app[k];
        b++;
        k++;
    }
    if (buf[b-1] == '\n')
        buf[b-1] = '\0';
    else
        buf[b] = '\0';
    return buf;
}

char    *place_str(char *sample, char *str_add, char *str)
{
    char    *buf;
    int     k;
    int     i;
    int     c;
    int     b;

    k = 0;
    i = 0;
    c = 1;
    b = 0;
    buf = (char*)malloc(sizeof(char) * (strlen(str) + 1));
    while (str[k])
    {
        if (str[k] == sample[i])
        {
            while (str[k] == sample[i])
            {
                buf[b] = str[k];
                k++;
                b++;
                i++;
            }
            if (sample[i] == '\0')
            {
                buf = realloc(buf, sizeof(char) * 
                                    (strlen(str) + c * strlen(str_add) + 1));
                i = 0;
                b -= strlen(sample);
                while (str_add[i])
                {
                    buf[b] = str_add[i];
                    b++;
                    i++;
                }
                c++;
                i = 0;
            }
            else
                i = 0;
        }
        else
        {
            buf[b] = str[k];
            k++;
            b++;
        }
    }
    buf[b-1] = '\0';
    return buf;
}

int     replace_string(t_doub_list *str_list, char *new_str)
{
    if (ptr->next)
    {
        ptr = ptr->next;
        delete_node(str_list, ptr->prev->num);
        str_num--;
        if (add_new_str(str_list, new_str) == LIST_ADD_ERR)
        {
            free(new_str);
            return LIST_ADD_ERR;
        }
    }
    else
    {
        delete_node(str_list, str_num);
        str_num--;
        if (add_new_str(str_list, new_str) == LIST_ADD_ERR)
        {
            free(new_str);
            return LIST_ADD_ERR;
        }
    }
    free(new_str);
    return 0;
}
int     replace_func(t_cmd_list *cmd, t_doub_list *str_list)
{
    char    *sample;
    char    *str_add;
    char    *new_str = NULL;
    int     rng;

    if (cmd->num_par < 3 || cmd->num_par > 5)
        return PARAMS_ERR;
    ptr = str_list->head;
    if (strcmp(cmd->params[0], "substring") == 0)
    {
        if (cmd->num_par == 5 && ft_atoi(cmd->params[1]) > 0)
        {
            if (ft_atoi(cmd->params[1]) > ft_atoi(cmd->params[2]))
                return PARAMS_ERR;
            if (ft_atoi(cmd->params[1]) > str_list->str_count || 
                                ft_atoi(cmd->params[2]) >str_list->str_count)
                return STR_COUNT_ERR;
            if (check_quotes(cmd->params[3]) && check_quotes(cmd->params[4]))
            {
                sample = unquoting(cmd->params[3]);
                str_add = unquoting(cmd->params[4]);
            }
            else if ((cmd->params[3][0] == '^' || cmd->params[3][0] == '&') 
                && cmd->params[3][1] == '\0' && check_quotes(cmd->params[4]))
            {
                sample = (char*)malloc(sizeof(char) * 2);
                sample[0] = cmd->params[3][0];
                sample[1] = '\0';
                str_add = unquoting(cmd->params[4]);
            }
            else
                return PARAMS_ERR;
            str_num = ft_atoi(cmd->params[1]);
            rng = ft_atoi(cmd->params[1]);
            while (rng != ptr->num)
                ptr = ptr->next;
            rng = ft_atoi(cmd->params[2]);
            rng -= ft_atoi(cmd->params[1]);
            rng++;
        }
        else if (cmd->num_par == 4)
        {
            if (ft_atoi(cmd->params[1]) <= 0)
                return PARAMS_ERR;
            rng = ft_atoi(cmd->params[1]);
            if (rng > str_list->str_count)
                return PARAMS_ERR;
            if (check_quotes(cmd->params[2]) && check_quotes(cmd->params[3]))
            {
                sample = unquoting(cmd->params[2]);
                str_add = unquoting(cmd->params[3]);
            }
            else if ((cmd->params[2][0] == '^' || cmd->params[2][0] == '&') 
                && cmd->params[2][1] == '\0' && check_quotes(cmd->params[3]))
            {
                sample = (char*)malloc(sizeof(char) * 2);
                sample[0] = cmd->params[2][0];
                sample[1] = '\0';
                str_add = unquoting(cmd->params[3]);
            }
            else
                return PARAMS_ERR;
            while (rng != ptr->num)
                ptr = ptr->next;
            str_num = ft_atoi(cmd->params[1]);
            rng = str_list->str_count - rng + 1;
        }
        else if (cmd->num_par == 3)
        {
            if (check_quotes(cmd->params[1]) && check_quotes(cmd->params[2]))
            {
                sample = unquoting(cmd->params[1]);
                str_add = unquoting(cmd->params[2]);
            }
            else if ((cmd->params[1][0] == '^' || cmd->params[1][0] == '&') 
                && cmd->params[1][1] == '\0' && check_quotes(cmd->params[2]))
            {
                sample = (char*)malloc(sizeof(char) * 2);
                sample[0] = cmd->params[1][0];
                sample[1] = '\0';
                str_add = unquoting(cmd->params[2]);
            }
            else
                return PARAMS_ERR;
            str_num = 1;
            rng = str_list->str_count;
        }
        else
            return PARAMS_ERR;
    }
    else
        return PARAMS_ERR;
    if (sample[0] == '^')
    {
        while (rng)
        {
            new_str = ft_strcat(str_add, ptr->str);
            new_str = sp_sym_handler(new_str);
            if (replace_string(str_list, new_str) == LIST_ADD_ERR)
                return LIST_ADD_ERR;
            rng--;
            str_num++;
        }
    }
    else if (sample[0] == '&')
    {
        while (rng)
        {
            new_str = ft_strcat(ptr->str, str_add);
            new_str = sp_sym_handler(new_str);
            if (replace_string(str_list, new_str) == LIST_ADD_ERR)
                return LIST_ADD_ERR;
            rng--;
            str_num++;
        }
    }
    else
    {
        while (rng)
        {
            if (strstr(ptr->str, sample))
            {
                new_str = place_str(sample, str_add, ptr->str);
                new_str = sp_sym_handler(new_str);
                if (replace_string(str_list, new_str) == LIST_ADD_ERR)
                    return LIST_ADD_ERR;
            }
            else
                ptr = ptr->next;
            rng--;
            str_num++;
        }
    }
    free(sample);
    free(str_add);
    return 0;
}
