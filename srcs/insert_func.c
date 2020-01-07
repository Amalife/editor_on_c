#include "std_n_def.h"
#include "func_pro.h"
#include "global.h"

int str_num;

int     check_quotes(char *str)
{
    int i;

    i = 0;
    if (str[i] == '"')
    {
        while(str[i])
            i++;
        if (str[i-1] == '"')
            return 1;
        else
            return 0;
    }
    else
        return 0;
}

char    *sp_sym_handler(char *str)
{
    char    *buf;
    int     k;
    int     size;

    k = 0;
    size = 0;
    buf = (char*)malloc(sizeof(char));
    while (str[k])
    {
        size++;
        buf = realloc(buf, sizeof(char) * (size + 1));
        if (str[k] == '\\' && str[k+1] == '\\')
        {
            buf[size-1] = '\\';
            k += 2;
        }
        else if (str[k] == '\\' && str[k+1] == '"')
        {
            buf[size-1] = '"';
            k += 2;
        }
        else if (str[k] == '\\' && str[k+1] == 't')
        {
            buf[size-1] = '\t';
            k += 2;
        }
        else if (str[k] == '\\' && str[k+1] == 'r')
        {
            buf[size-1] = '\r';
            k += 2;
        }
        else if (str[k] == '\\' && str[k+1] == 'n')
        {
            buf[size-1] = '\n';
            k += 2;
        }
        else
        {
            buf[size-1] = str[k];
            k++;
        }
    }
    buf[size] = '\0';
    free (str);
    return buf;

}

int     insert_str(t_doub_list *str_list, char *str)
{
    t_node  *node;
    t_node  *ptr;
    int     k;

    k = 0;
    ptr = str_list->head;
    node = (t_node*)malloc(sizeof(t_node));
    if (node)
    {
        node->str = (char*)malloc(sizeof(char) * (strlen(str) + 1));
        while (str[k])
        {
            node->str[k] = str[k];
            k++;
        }
        node->str[k] = '\0';
        while (str_num != 0 && str_num != ptr->num)
            ptr = ptr->next;
        node->width = strlen(node->str);
        node->num = str_num + 1;
        str_list->str_count++;
        if (str_num == 0)
        {
            node->prev = NULL;
            ptr->prev = node;
            node->next = ptr;
            str_list->head = node;
        }
        else
        {
            if (ptr->next)
            {
                ptr->next->prev = node;
                node->next = ptr->next;
            }
            else
                node->next = NULL;
            node->prev = ptr;
            ptr->next = node;
            ptr = ptr->next->next;
        }
        if (node->num == str_list->str_count)
            str_list->tail = node;
        ft_putstr("String inserted\n");
        str_list->flags[F_CHANGED] = 1;
        while (ptr)
        {
            ptr->num++;
            ptr = ptr->next;
        }
    }
    else
        return LIST_ADD_ERR;
    return 0;
}

int     add_new_str(t_doub_list *str_list, char *str)
{
    char    *buf;
    int     k;
    int     size;

    k = 0;
    size = 0;
    buf = (char*)malloc(sizeof(char));
    while (str[k])
    {
        size++;
        buf = realloc(buf, sizeof(char) * (size + 1));
        buf[size-1] = str[k];
        if (str[k] == '\n')
        {
            buf[size] = '\0';
            if (insert_str(str_list, buf) == LIST_ADD_ERR)
            {
                free(buf);
                return LIST_ADD_ERR;
            }
            free(buf);
            size = 0;
            buf = (char*)malloc(sizeof(char));
            str_num++;
        }
        k++;
    }
    size++;
    buf = realloc(buf, sizeof(char) * (size + 1));
    buf[size-1] = '\n';
    buf[size] = '\0';
    if (insert_str(str_list, buf) == LIST_ADD_ERR)
    {
        free(buf);
        return LIST_ADD_ERR;
    }
    str_num++;
    free(buf);
    return 0;
}

int     insert_sym(t_doub_list *str_list, char **params)
{
    char    *new_str = NULL;
    char    *buf = NULL;
    int     pos;
    char    sym;
    int     i;
    t_node  *ptr;

    i = 0;
    ptr = str_list->head;
    if (strlen(params[3]) == 1)
        sym = params[3][0];
    else if (strlen(params[3]) == 2 && params[3][0] == '\\')
    {
        buf = sp_sym_handler(params[3]);
        if (buf[1] == '\0')
            sym = buf[0];
        else
        {
            params[3] = buf;
            return SP_SYM_ERR;
        }
    }
    else
        return PARAMS_ERR;
    str_num = ft_atoi(params[1]);
    if (str_num > str_list->str_count)
        return PARAMS_ERR;
    pos = ft_atoi(params[2]);
    while (str_num != ptr->num)
        ptr = ptr->next;
    ptr->str = realloc(ptr->str, sizeof(char) * 
                                        (strlen(ptr->str) + 2));
    i = strlen(ptr->str) + 1;
    if (pos < 0)
        pos = 1;
    else if (pos > ptr->width)
        pos = ptr->width;
    while (i != pos)
    {
        ptr->str[i] = ptr->str[i-1];
        i--;
    }
    ptr->str[i] = ptr->str[i-1];
    ptr->str[pos-1] = sym;
    i = 0;
    if (sym == '\n')
    {
        new_str = (char*)malloc(sizeof(char) * (strlen(ptr->str) + 2));
        while (ptr->str[i])
        {
            new_str[i] = ptr->str[i];
            i++;
        }
        new_str[i-1] = '\0';
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
        str_list->head->width++;
    str_list->flags[F_CHANGED] = 1;
    ft_putstr("Symbol inserted\n");
    if (buf)
        params[3] = buf;
    return 0;
}

int     insert_group(t_doub_list *str_list)
{
    char    *buf;
    int     size;
    int     ch;

    do
    {
        buf = (char*)malloc(sizeof(char));
        size = 0;
        while ((ch = getchar()) != '\n')
        {
            size++;
            buf = realloc(buf, sizeof(char) * (size + 1));
            buf[size-1] = ch;
        }
        buf[size] = '\0';
        if (strcmp(buf, "\"\"\""))
        {
            buf = sp_sym_handler(buf);
            if (add_new_str(str_list, buf) == LIST_ADD_ERR)
            {
                free(buf);
                return LIST_ADD_ERR;
            }
            free(buf);
        }
        else
            break;
    } while (1);
    free(buf);
    return 0;
}

int     insert_func(t_cmd_list *cmd, t_doub_list *str_list)
{
    char    *buf;

    str_num = 0;
    if (str_list->flags[F_FILE] == 0)
        return NO_FILE_ERR;
    if (cmd->num_par == 0 || cmd->num_par > 4)
        return PARAMS_ERR;
    if (strcmp(cmd->params[0], "after") == 0)
    {
        str_num = ft_atoi(cmd->params[1]);
        if (str_num >= 0 && str_num <= str_list->str_count && cmd->num_par == 3
                                            && check_quotes(cmd->params[2]))
        {
            if (strcmp(cmd->params[2], "\"\"\"") == 0)
                return insert_group(str_list);
            buf = unquoting(cmd->params[2]);
            buf = sp_sym_handler(buf);
            if (add_new_str(str_list, buf) == LIST_ADD_ERR)
            {
                free(buf);
                return LIST_ADD_ERR;
            }
        }
        else if (cmd->num_par == 2 && check_quotes(cmd->params[1]))
        {
            str_num = str_list->str_count;
            if (strcmp(cmd->params[1], "\"\"\"") == 0)
                return insert_group(str_list);
            buf = unquoting(cmd->params[1]);
            buf = sp_sym_handler(buf);
            if (add_new_str(str_list, buf) == LIST_ADD_ERR)
            {
                free(buf);
                return LIST_ADD_ERR;
            }
        }
        else
            return PARAMS_ERR;
        free(buf);    
    }
    else if (strcmp (cmd->params[0], "symbol") == 0)
    {
        if (cmd->num_par == 4 && ft_atoi(cmd->params[1]) > 0)
            return (insert_sym(str_list, cmd->params));
        else
            return PARAMS_ERR;
    }
    else
        return PARAMS_ERR;
    return 0;
}
