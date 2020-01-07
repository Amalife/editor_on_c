#include "std_n_def.h"
#include "func_pro.h"
#include "global.h"

t_doub_list *str_list;

int main()
{
    char        *buf;
    t_cmd_list  *cmd;
    int         r;
    int         i;
    int         size;
    int         ch;

    str_list = (t_doub_list*)malloc(sizeof(t_doub_list));
    str_list->tail = NULL;
    str_list->head = NULL;
    str_list->flags = (int*)calloc(NUM_OF_FLAGS, sizeof(int));
    str_list->file_link = NULL;
    str_list->tab_width = 4;
    signal(SIGWINCH, chg_size);
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
        cmd = (t_cmd_list*)malloc(sizeof(t_cmd_list));
        cmd_template(buf, cmd);
        free(buf);
        printf("name: %s\n", cmd->key_word);
        if (cmd->params)
            while (cmd->params[i])
            {
                printf("the %d argument: %s\n", i, cmd->params[i]);
                i++;
            }
        i = 0;
        switch(read_n_det(cmd))
        {
            case EXIT_NUM:
                r = editor_exit(cmd, str_list);
                break;
            case READ_NUM:
                r = editor_read_n_open(cmd, str_list);
                break;
            case OPEN_NUM:
                str_list->flags[F_OPEN] = 1;
                r = editor_read_n_open(cmd, str_list);
                break;
            case WRITE_NUM:
                ft_putstr("saving file\n");
                str_list->flags[F_CHANGED] = 0;
                break;
            case PRINT_NUM:
                str_list->flags[F_PRINT] = 1;
                r = print(cmd, str_list);
                str_list->flags[F_PRINT] = 0;
                break;
            case SET_NUM:
                r = set_func(cmd, str_list);
                break;
            case INSERT_NUM:
                r = insert_func(cmd, str_list);
                break;
            case EDIT_NUM:
                r = edit_func(cmd, str_list);
                break;
            case REPLACE_NUM:
                r = replace_func(cmd, str_list);
                break;
            case DELETE_NUM:
                r = delete_func(cmd, str_list);
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
        free(cmd->params);
        free(cmd);
    }
    list_free(str_list);
    printf("return check = %d\n", r);
    return 0;
}
