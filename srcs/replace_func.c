#include "std_n_def.h"
#include "func_pro.h"
#include "global.h"

int     str_num;
int     tmp;
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

char    *com_str(char sym)
{
    char    *buf;
    int     k;
    int     size;

    k = 0;
    size = 0;
    if (sym == '/')
    {
        buf = (char*)malloc(sizeof(char));
        while (ptr->str[k])
        {
            if (ptr->str[k] == '/' && ptr->str[k+1] == '/')
                ptr->str[k+1] = '\0';
            else
            {
                size++;
                buf = realloc(buf, sizeof(char) * (size + 1));
                buf[size-1] = ptr->str[k];
            }
            k++;
        }
        buf[size] = '\0';
    }
    else if (sym == '#')
    {
        buf = (char*)malloc(sizeof(char));
        while (ptr->str[k])
        {
            if (ptr->str[k] == '#')
                ptr->str[k+1] = '\0';
            else
            {
                size++;
                buf = realloc(buf, sizeof(char) * (size + 1));
                buf[size-1] = ptr->str[k];
            }
            k++;
        }
        buf[size] = '\0';
    }
    return buf;
}

char    *block_com_str(char sym)
{
    char    *buf;
    int     k;
    int     size;
    t_node  *s_ptr;

    k = 0;
    size = 0;
    tmp = 1;
    s_ptr = ptr;
    if (sym == '{')
    {
        buf = (char*)malloc(sizeof(char));
        while (ptr->str[k])
        {
            if (ptr->str[k] == '{')
            {
                while (ptr->str[k])
                {
                    if (ptr->str[k] == '}')
                    {
                        k++;
                        while (ptr->str[k])
                        {
                            size++;
                            buf = realloc(buf, sizeof(char) * (size + 1));
                            buf[size-1] = ptr->str[k];
                            k++;
                        }
                        break;
                    }
                    else
                    {
                        k++;
                        if (ptr->str[k] == '\0' && ptr)
                        {
                            ptr = ptr->next;
                            k = 0;
                            tmp++;
                        }
                    }
                }
                break;
            }
            else
            {
                size++;
                buf = realloc(buf, sizeof(char) * (size + 1));
                buf[size-1] = ptr->str[k];
            }
            k++;
        }
        buf[size] = '\0';
    }
    else if (sym == '/')
    {
        buf = (char*)malloc(sizeof(char));
        while (ptr->str[k])
        {
            if (ptr->str[k] == '/' && ptr->str[k+1] == '*')
            {
                while (ptr->str[k])
                {
                    if (ptr->str[k] == '*' && ptr->str[k+1] == '/')
                    {
                        k += 2;
                        while (ptr->str[k])
                        {
                            size++;
                            buf = realloc(buf, sizeof(char) * (size + 1));
                            buf[size-1] = ptr->str[k];
                            k++;
                        }
                        break;
                    }
                    else
                    {
                        k++;
                        if (ptr->str[k] == '\0' && ptr)
                        {
                            ptr = ptr->next;
                            k = 0;
                            tmp++;
                        }
                    }
                }
                break;
            }
            else
            {
                size++;
                buf = realloc(buf, sizeof(char) * (size + 1));
                buf[size-1] = ptr->str[k];
            }
            k++;
        }
        buf[size] = '\0';
    }
    ptr = s_ptr;
    return buf;
}

void    delete_pascal(t_doub_list *str_list)
{
    int     k;
    int     ind;
    int     f_rep;
    char    *new_str = NULL;

    k = 0;
    ind = 0;
    f_rep = 0;
    ptr = str_list->head;
    while (ptr)
    {
        while (ptr->str[k])
        {
            if (ptr->str[k] == '\'')
                ind = (ind + 1) % 2;
            if (ind == 0 && ptr->str[k] == '{')
            {
                new_str = block_com_str('{');
                while (tmp)
                {
                    if (ptr->next)
                    {
                        ptr = ptr->next;
                        delete_node(str_list, ptr->prev->num);
                    }
                    else
                        delete_node(str_list, ptr->prev->num);
                    tmp--;
                }
                str_num = ptr->prev->num;
                add_new_str(str_list, new_str);
                free(new_str);
                f_rep = 1;
                break;
            }
            if (ind == 0 && ptr->str[k] == '/' && ptr->str[k+1] == '/')
            {
                new_str = com_str('/');
                replace_string(str_list, new_str);
                f_rep = 1;
                break;
            }
            else
                k++;
        }
        k = 0;
        if (f_rep)
            f_rep = 0;
        else
            ptr = ptr->next;
        if (ptr)
            str_num = ptr->num;
    }
}

void    delete_c(t_doub_list *str_list)
{
    int     k;
    int     ind;
    int     f_rep;
    char    *new_str = NULL;

    k = 0;
    ind = 0;
    f_rep = 0;
    ptr = str_list->head;
    while (ptr)
    {
        while (ptr->str[k])
        {
            if (ptr->str[k] == '"')
                ind = (ind + 1) % 2;
            if (ind == 0 && ptr->str[k] == '/')
            {
                new_str = block_com_str('/');
                while (tmp)
                {
                    if (ptr->next)
                    {
                        ptr = ptr->next;
                        delete_node(str_list, ptr->prev->num);
                    }
                    else
                        delete_node(str_list, ptr->prev->num);
                    tmp--;
                }
                str_num = ptr->prev->num;
                add_new_str(str_list, new_str);
                free(new_str);
                f_rep = 1;
                break;
            }
            else
                k++;
        }
        k = 0;
        if (f_rep)
            f_rep = 0;
        else
            ptr = ptr->next;
        if (ptr)
            str_num = ptr->num;
    }
}

void    delete_cpp(t_doub_list *str_list)
{
    int     k;
    int     ind;
    int     f_rep;
    char    *new_str = NULL;

    k = 0;
    ind = 0;
    f_rep = 0;
    ptr = str_list->head;
    while (ptr)
    {
        while (ptr->str[k])
        {
            if (ptr->str[k] == '"')
                ind = (ind + 1) % 2;
            if (ind == 0 && ptr->str[k] == '/' && ptr->str[k+1] == '/')
            {
                new_str = com_str('/');
                replace_string(str_list, new_str);
                f_rep = 1;
                break;
            }
            else
                k++;
        }
        k = 0;
        if (f_rep)
            f_rep = 0;
        else
            ptr = ptr->next;
        if (ptr)
            str_num = ptr->num;
    }
}

void    delete_shell(t_doub_list *str_list)
{
    int     k;
    int     ind_one;
    int     ind_two;
    int     f_rep;
    char    *new_str = NULL;

    k = 0;
    ind_one = 0;
    ind_two = 0;
    f_rep = 0;
    ptr = str_list->head;
    while (ptr)
    {
        while (ptr->str[k])
        {
            if (ptr->str[k] == '\'')
                ind_one = (ind_one + 1) % 2;
            else if (ptr->str[k] == '"')
                ind_two = (ind_two + 1) % 2;
            if (ind_one == 0 && ind_two == 0 && ptr->str[k] == '#')
            {
                new_str = com_str('#');
                replace_string(str_list, new_str);
                f_rep = 1;
                break;
            }
            else
                k++;
        }
        k = 0;
        if (f_rep)
            f_rep = 0;
        else
            ptr = ptr->next;
        if (ptr)
            str_num = ptr->num;
    }
}

int     com_handler(t_doub_list *str_list, char *com_type)
{
    str_num = 1;
    if (strcmp(com_type, "pascal") == 0)
        delete_pascal(str_list);
    else if (strcmp(com_type, "c") == 0)
        delete_c(str_list);
    else if (strcmp(com_type, "c++") == 0)
        delete_cpp(str_list);
    else if (strcmp(com_type, "shell") == 0)
        delete_shell(str_list);
    else
        return PARAMS_ERR;
    ft_putstr("Comments deleted\n");
    return 0;
}
