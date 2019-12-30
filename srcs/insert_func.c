#include "std_n_def.h"
#include "func_pro.h"
#include "global.h"

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

int     check_sp_sym(char *str)
{
    int i;
    int k;
    int sp;

    i = 0;
    k = 0;
    sp = 0;
    while (str[k] && sp == 0)
    {
        while (str[k] && str[k] == '\\' && sp == 0)
        {
            i++;
            if (str[k+1] == 'n' || str[k+1] == 'r' || str[k+1] == 't')
                if (i % 2 == 1)
                    sp = 1;
            k++;
        }
        if (str[k] && sp == 0)
        {
            i = 0;
            k++;
        }
    }
    if (i % 2 == 1 && sp)
        return 1;
    else
        return 0;
}

char    *sp_sym_handler(char *str, t_doub_list *str_list, int str_num)
{
    char    *buf;
    int     i;
    int     k;
    int     n;

    k = 0;
    n = 0;
    i = 0;
    while ((str[k] != '\\' || str[k+1] != 'n') && str[k])
        {
            if (str[k] == '\\' && str[k+1] == 't')
            {
                n += 4;
                k += 2;
            }
            else
            {
                k++;
                n++;
            }
        }
    buf = (char*)malloc(sizeof(char) * (n + 2));
    k = 0;
    while ((str[k] != '\\' || str[k+1] != 'n') && str[k])
    {
        if (str[k] == '\\' && str[k+1] == 't')
        {
            buf[i] = '\t';
            i++;
            k += 2;
        }
        else if (str[k] == '\\' && str[k+1] == 'r')
        {
            buf[i] = '\r';
            i++;
            k += 2;
        }
        else
        {
            buf[i] = str[k];
            i++;
            k++;
        }
    }
    if (n == 0)
    {
        buf[i] = '\n';
        i++;
    }
    buf[i] = '\0';
    if (add_new_str(str_list, str_num, buf) == LIST_ADD_ERR)
        return NULL;
    n = strlen(str);
    if (n > k)
    {
        buf = realloc(buf, sizeof(char) * (n - k - 1));
        i = 0;
        k += 2;
        while (str[k])
        {
            buf[i] = str[k];
            i++;
            k++;
        }
        buf[i] = '\0';
    }
    else
    {
        buf = (char*)malloc(sizeof(char));
        buf[0] = '\0';
    }
    free (str);
    return buf;

}

int     add_new_str(t_doub_list *str_list, int str_num, char *params)
{
    
    t_node  *node;
    t_node  *save;
    int     i;
    int     j;

    i = 0;
    j = 0;
    save = str_list->head;
    node = (t_node*)malloc(sizeof(t_node));
    if (node)
    {
        if (params[j] == '\0')
            return 0;
        else if (params[j] == '\n')
            node->str = (char*)malloc(sizeof(char) * 2);
        else
            node->str = (char*)malloc(sizeof(char) * (strlen(params) - 1));
        while (params[j])
        {
            while (params[j] == '\\' && params[j+1] == '\\')
            {
                node->str[i] = '\\';
                j += 2;
                i++;
            }
            if (params[j])
            {
                node->str[i] = params[j];
                j++;
                i++;
            }
        }
        if (node->str[i-1] != '\n')
        {
            node->str[i] = '\n';
            i++;
        }
        node->str[i] = '\0';
        while (str_num != str_list->head->num && str_num != 0)
            str_list->head = str_list->head->next;
        node->width = strlen(node->str) + 1;
        node->num = str_num + 1;
        str_list->str_count++;
        if (str_num == 0)
        {
            node->prev = NULL;
            str_list->head->prev = node;
            node->next = str_list->head;
            save = node;
            str_list->head = node->next;
        }
        else
        {
            if (str_list->head->next)
            {
                str_list->head->next->prev = node;
                node->next = str_list->head->next;
            }
            else
                node->next = NULL;
            node->prev = str_list->head;
            str_list->head->next = node;
            str_list->head = str_list->head->next->next;
        }
        ft_putstr("Inserted\n");
        str_list->flags[F_CHANGED] = 1;
        while (str_list->head)
        {
            str_list->head->num++;
            str_list->head = str_list->head->next;
        }
    }
    else
        return LIST_ADD_ERR;
    str_list->head = save;
    return 0;
}

int     insert_sym(t_doub_list *str_list, char **params)
{
    int     str;
    int     pos;
    char    sym;
    t_node  *save;
    int     i;

    if (strlen(params[3]) == 1)
        sym = params[3][0];
    else
        return PARAMS_ERR;
    str = ft_atoi(params[1]);
    if (str > str_list->str_count)
        return PARAMS_ERR;
    pos = ft_atoi(params[2]);
    save = str_list->head;
    while (str != str_list->head->num)
        str_list->head = str_list->head->next;
    str_list->head->str = realloc(str_list->head->str, sizeof(char) * 
                                        (strlen(str_list->head->str) + 2));
    i = strlen(str_list->head->str) + 1;
    if (pos <= 0)
        pos = 1;
    else if (pos >= str_list->head->width)
        pos = str_list->head->width;
    while (i != (pos - 1))
    {
        str_list->head->str[i] = str_list->head->str[i-1];
        i--;
    }
    str_list->head->str[pos-1] = sym;
    str_list->head = save;
    str_list->head->width++;
    str_list->flags[F_CHANGED] = 1;
    return 0;
}

int     insert_group(t_doub_list *str_list, int str_num)
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
            while (check_sp_sym(buf))
            {
                buf = sp_sym_handler(buf, str_list, str_num);
                str_num++;
            }
            if (add_new_str(str_list, str_num, buf) == LIST_ADD_ERR)
            {
                free(buf);
                return LIST_ADD_ERR;
            }
            str_num++;
            free(buf);
        }
    } while (strcmp(buf, "\"\"\""));
    free(buf);
    return 0;
}

int     insert_func(char **params, t_doub_list *str_list)
{
    int     str_num;
    char    *buf;

    str_num = 0;
    if (strcmp(params[0], "after") == 0)
    {
        str_num = ft_atoi(params[1]);
        if (str_num >= 0 && str_num <= str_list->str_count && params[2]
                                                    && check_quotes(params[2]))
        {
            if (strcmp(params[2], "\"\"\"") == 0)
                return insert_group(str_list, str_num);
            buf = unqouting(params[2]);
            while (check_sp_sym(buf))
            {
                buf = sp_sym_handler(buf, str_list, str_num);
                str_num++;
            }
            if (add_new_str(str_list, str_num, buf) == LIST_ADD_ERR)
            {
                free(buf);
                return LIST_ADD_ERR;
            }
        }
        else if (params[1] && check_quotes(params[1]))
        {
            str_num = str_list->str_count;
            if (strcmp(params[1], "\"\"\"") == 0)
                return insert_group(str_list, str_num);
            buf = unqouting(params[1]);
            while (check_sp_sym(buf))
            {
                buf = sp_sym_handler(buf, str_list, str_num);
                str_num++;
            }
            if (add_new_str(str_list, str_num, buf) == LIST_ADD_ERR)
            {
                free(buf);
                return LIST_ADD_ERR;
            }
        }
        else
            return PARAMS_ERR;
            
    }
    else if (strcmp (params[0], "symbol") == 0)
    {
        if (params[4] && ft_atoi(params[1]) <= 0)
            return PARAMS_ERR;
        else
            return (insert_sym(str_list, params));
    }
    else
        return PARAMS_ERR;
    free(buf);
    return 0;
}
