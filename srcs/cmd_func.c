#include "std_n_def.h"
#include "global.h"
#include "func_pro.h"

int     editor_exit(t_cmd_list *cmd, t_doub_list *str_list)
{
    if (cmd->num_par > 1)
        return PARAMS_ERR;
    else if (cmd->num_par == 1 && strcmp(cmd->params[0], "force") == 0)
        str_list->flags[F_CHANGED] = 0;
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

int     editor_write(t_cmd_list *cmd, t_doub_list *str_list)
{
    FILE    *fd;
    char    *path;
    t_node  *ptr;
    
    ptr = str_list->head;
    if (cmd->num_par == 0)
    {
        if (str_list->file_link == NULL)
            return NO_FILE_LINK;
        fd = fopen(str_list->file_link, "w+");
        while (ptr)
        {
            fwrite(ptr->str, sizeof(char), strlen(ptr->str), fd);
            ptr = ptr->next;
        }
        fclose(fd);
    }
    else if (cmd->num_par == 1 && check_quotes(cmd->params[0]))
    {
        path = unquoting(cmd->params[0]);
        fd = fopen(path, "w+");
        while (ptr)
        {
            fwrite(ptr->str, sizeof(char), strlen(ptr->str), fd);
            ptr = ptr->next;
        }
        fclose(fd);
        free(path);
    }
    else
        return PARAMS_ERR;
    ft_putstr("File saved\n");
    return 0;
}

void    list_free(t_doub_list *str_list)
{
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

int     append_to_list(char *str, t_doub_list *str_list)
{
    t_node  *node;
    int     size;
    int     i;

    size = 0;
    i = 0;
    node = (t_node*)malloc(sizeof(t_node));
    if (node && str_list)
    {
        node->width = 0;
        node->str = (char*)malloc(sizeof(char));
        while (str[i])
        {
            size++;
            if (str[i] == '\t')
                node->width += str_list->tab_width;
            node->str = realloc(node->str, sizeof(char) * (size + 1));
            node->str[size-1] = str[i];
            i++;
        }
        node->str[size] = '\0';
        node->num = str_list->str_count;;
        node->width += strlen(node->str);
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
    char    *buf;
    char    *str;
    int     i;
    int     c;

    list_free(str_list);
    buf = read_file(fd);
    fclose(fd);
    str_list->str_count = 0;
    c = 0;
    while (buf[c])
    {
        i = 0;
        str_list->str_count++;
        str = (char*)malloc(sizeof(char));
        do
        {
            i++;
            str = realloc(str, sizeof(char) * (i + 1));
            str[i-1] = buf[c];
            c++;
        } while (buf[c-1] != '\n' && buf[c]);
        str[i] = '\0';
        if (append_to_list(str, str_list))
            return LIST_ADD_ERR;
        free(str);
    }
    free (buf);
    if (str_list->flags[F_OPEN])
    {
        ft_putstr("File opened: ");
        ft_putstr(str_list->file_link);
        ft_putchar('\n');
        str_list->flags[F_OPEN] = 0;
    }
    else
        ft_putstr("File read\n");
    str_list->flags[F_FILE] = 1;
    return 0;
}

char    *unquoting(char *str)
{
    char    *buf;
    int     j;
    int     i;

    j = 0;
    i = 1;
    buf = (char*)malloc(strlen(str) - 1);
    while (str[i])
    {
        buf[j] = str[i];
        j++;
        i++;
    }
    buf[j-1] = '\0';
    return buf;
}

int     editor_read_n_open(t_cmd_list *cmd, t_doub_list *str_list)
{
    FILE    *fd;
    char    *file;

    if (cmd->num_par != 1)
        return PARAMS_ERR;
    if (check_quotes(cmd->params[0]) == 0)
        return PARAMS_ERR;
    file = unquoting(cmd->params[0]);
    fd = fopen(file, "r+");
    if (fd == NULL)
    {
        free(file);
        return OPEN_FILE_ERR;
    }
    if (str_list->flags[F_OPEN])
    {
        if (str_list->file_link)
            free(str_list->file_link);
        str_list->file_link = file;
    }
    else
        free(file);
    return make_list(str_list, fd);
}
