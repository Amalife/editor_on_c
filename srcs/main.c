#include "std_n_def.h"
#include "func_pro.h"
#include "global.h"

int main()
{
    char        *buf;
    t_cmd_list  *cmd;
    int         r;
    int         i;
    int         size;
    int         ch;
    t_doub_list *str_list;

    str_list = (t_doub_list*)malloc(sizeof(t_doub_list));
    str_list->flags = (int*)calloc(NUM_OF_FLAGS, sizeof(int));
    str_list->file_link = NULL;
    str_list->tab_width = 4;
    while (str_list->flags[F_CHANGED] || str_list->flags[F_EXIT] == 0)
    {
        ft_putstr("Editor:");
        size = 0;
        i = 0;
        buf = (char*)malloc(sizeof(char));
        while ((ch = getchar()) != '\n')
        {
            size++;
            buf = realloc(buf, sizeof(char) * (size + 1));
            buf[size-1] = ch;
        }
        buf[size] = '\0';
        cmd = ft_cmd_template(buf);
        free(buf);
        switch(read_n_det(cmd))
        {
            case EXIT_NUM:
                r = editor_exit(cmd->params, str_list);
                break;
            case READ_NUM:
                r = editor_read_n_open(cmd->params, str_list);
                break;
            case OPEN_NUM:
                str_list->flags[F_OPEN] = 1;
                r = editor_read_n_open(cmd->params, str_list);
                break;
            case WRITE_NUM:
                ft_putstr("saving file\n");
                str_list->flags[F_CHANGED] = 0;
                break;
            case PRINT_NUM:
                r = print(cmd->params, str_list);
                break;
            case SET_NUM:
                r = set_func(cmd->params, str_list);
                break;
            case INSERT_NUM:
                r = insert_func(cmd->params, str_list);
                break;
            case EDIT_NUM:
                r = edit_func(cmd->params, str_list);
                break;
            case REPLACE_NUM:
                r = replace_func(cmd->params, str_list);
                break;
            default:
                ft_putstr("wrong command\n");
        }
        free(cmd->key_word);
        if (cmd->params)
            while (cmd->params[i])
            {
                free(cmd->params[i]);
                i++;
            }
        free(cmd);
    }
    list_free(str_list);
    printf("return check = %d\n", r);
    return 0;
}
