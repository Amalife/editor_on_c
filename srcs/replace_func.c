#include "std_n_def.h"
#include "func_pro.h"
#include "global.h"

char    *ft_strcat(char *dest, char *src)
{
    int i;
    int j;

    i = 0;
    j = 0;
    dest = realloc(dest, sizeof(char) * (strlen(dest) + strlen(src) + 1));
    while (dest[i])
        i++;
    while (src[j])
    {
        dest[i] = src[j];
        i++;
        j++;
    }
    dest[i] = '\0';
    return dest;
}

char    *place_str(char *add_str, t_node *head, int k)
{
    char    *buf;
    int     i;

    i = 0;
    buf = (char*)malloc(sizeof(char) * (strlen(head->str) - k + 1));
    while (i != k)
    {
        buf[i] = head->str[i];
        i++;
    }
    buf[i] = '\0';
    buf = ft_strcat(buf, add_str);
    i += strlen(add_str);
    while (head->str[k])
    {
        buf[i] = head->str[k];
        i++;
        k++;
    }
    buf[i] = '\0';
    return buf;
}

void    check_str(char *sample, char *add_str, t_node *head)
{
    int     k;
    int     i;
    int     same;
    char    *buf;

    k = 0;
    i = 0;
    same = 0;
    while (head->str[k])
    {
        while (sample[i] && head->str[k] == sample[i])
        {
                puts("check");
            i++;
            k++;
            if (sample[i] == '\0')
                same = 1;
        }
        if (same == 1)
        {
            buf = place_str(add_str, head, k);
            free(head->str);
            head->str = buf;
            k += strlen(add_str) - 1;
            same = 0;
        }
        i = 0;
        if (head->str[k])
            k++;
    }
}

int     replace_func(char **params, t_doub_list *str_list)
{
    t_node  *save;
    char    *first;
    char    *second;

    if (strcmp(params[0], "substring"))
        return PARAMS_ERR;
    if (params[3] == NULL)
    {
        save = str_list->head;
        while (str_list->head)
        {
            first = unqouting(params[1]);
            free(params[1]);
            second = unqouting(params[2]);
            free(params[2]);
            check_str(first, second, str_list->head);
            str_list->head = str_list->head->next;
        }
    }
    else
        return PARAMS_ERR;
    str_list->head = save;
    return 0;
}
