#include "std_n_def.h"
#include "global.h"
#include "func_pro.h"

int     editor_exit(char **params, t_doub_list *str_list)
{
    if (params)
    {
        if (params[1])
            return PARAMS_ERR;
        else if (params[0] && strcmp(params[0], "force") == 0)
            str_list->flags[F_CHANGED] = 0;
        else
            return PARAMS_ERR;
    }
    if (str_list->flags[F_CHANGED])
    {
        ft_putstr("The file is not saved\n");
        return NOT_SAVED;
    }
    else
    {
        str_list->flags[F_EXIT] = 1;
        ft_putstr("Exit the editor\n");
    }
    return 0;
}

int     ft_strlen_news(char *str, int cur)
{
    while(str[cur] != '\n')
        cur++;
    return cur;
}

int     ft_count_news(char *str)
{
    int i;

    i = 0;
    while (*str)
    {
        if(*str == '\n')
            i++;
        str++;
    }
    return i;
}

void    list_free(t_doub_list *str_list)
{
    if (str_list->str_width)
        free(str_list->str_width);
    while (str_list->tail)
    {
        if (str_list->tail->prev)
        {
            str_list->tail = str_list->tail->prev;
            free(str_list->tail->next->str);
            free(str_list->tail->next);
        }
        else
        {
            free(str_list->tail->str);
            free(str_list->tail);
            str_list->tail = NULL;
        }
    }
    if (str_list->flags[F_EXIT])
    {
        if (str_list->file_link)
            free(str_list->file_link);
        free(str_list->flags);
        free(str_list);
    }
}

int     append_to_list(char *buf, t_doub_list *str_list, int c, int i)
{
    t_node  *node;
    int     k;

    k = 0;
    node = (t_node*)malloc(sizeof(t_node));
    if (node && str_list)
    {
        node->width = str_list->str_width[i] - str_list->str_width[i-1];
        node->str = (char*)malloc(sizeof(char) * (node->width + 1));
        while (buf[c] != '\n' && buf)
        {
            if (buf[c] == '\t')
                node->width += str_list->tab_width;
            node->str[k] = buf[c];
            k++;
            c++;
        }
        node->str[k] = '\n';
        k++;
        node->str[k] = '\0';
        node->num = i;
        node->prev = str_list->tail;
        node->next = NULL;
        if (str_list->tail)
            str_list->tail->next = node;
        else
        {
            node->prev = NULL;
            str_list->head = node;
        }
        str_list->tail = node;
        return 0;
    }
    return -1;
}

char    *read_file(FILE *fd)
{
    char    *buf;
    int     size;

    fseek(fd, 0, SEEK_END);
    size = ftell(fd);
    buf = (char*)calloc(size + 1, sizeof(char));
    fseek(fd, 0, SEEK_SET);
    fread(buf, size, sizeof(char), fd);
    return buf;
}

int     make_list(t_doub_list *str_list, FILE *fd)
{
    char        *buf;
    int         i;
    int         c;

    list_free(str_list);
    buf = read_file(fd);
    fclose(fd);
    i = ft_count_news(buf);
    str_list->str_count = i;
    str_list->str_width = (int*)malloc(sizeof(int) * (i + 1));
    str_list->str_width[0] = 0;
    i = 1;
    c = 0;
    while (buf[c])
    {
        str_list->str_width[i] = ft_strlen_news(buf, c);
        if (append_to_list(buf, str_list, c, i))
            return LIST_ADD_ERR;
        c = str_list->str_width[i] + 1;
        i++;
    }
    free (buf);
    if (str_list->flags[F_OPEN])
    {
        ft_putstr("File opened:");
        ft_putstr(str_list->file_link);
        ft_putchar('\n');
        str_list->flags[F_OPEN] = 0;
    }
    else
        ft_putstr("File read\n");
    return 0;
}

char    *unqouting(char *str)
{
    char    *buf;
    int     j;
    int     i;

    j = 0;
    i = 1;
    buf = (char*)malloc(ft_strlen(str) - 2);
    while (str[i])
    {
        buf[j] = str[i];
        j++;
        i++;
    }
    buf[j-1] = '\0';
    return buf;
}

int     editor_read_n_open(char **params, t_doub_list *str_list)
{
    FILE    *fd;
    int     i;
    int     j;

    i = 0;
    j = 0;
    if (params[0] == NULL || params[1])
        return PARAMS_ERR;
    if (str_list->flags[F_CHANGED])
    {
        ft_putstr("You have an unsaved file\n");
        return NOT_SAVED;
    }
    fd = fopen(unqouting(params[0]), "r+");
    if (fd == NULL)
        return OPEN_FILE_ERR;
    if (str_list->flags[F_OPEN])
    {
        if (str_list->file_link)
            free(str_list->file_link);
        str_list->file_link = (char*)malloc(sizeof(char) * 
                                        (ft_strlen(params[0]) - 2));
        while (params[0][i])
        {
            if (params[0][i] != '"')
            {
                str_list->file_link[j] = params[0][i];
                j++;
            }
            i++;
        }
        str_list->file_link[i] = '\0';
    }
    else
        str_list->flags[F_CHANGED] = 1;
    return make_list(str_list, fd);
}
