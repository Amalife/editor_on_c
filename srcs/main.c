#include "std_n_def.h"
#include "func_pro.h"
#include "global.h"

t_doub_list *str_list = NULL;
//t_doub_list *help_list = NULL;

void    init(char **argv, int argc)
{
    FILE    *fd;
    char    *file;
    int     k;

    k = 0;
    str_list = (t_doub_list*)malloc(sizeof(t_doub_list));
    str_list->tail = NULL;
    str_list->head = NULL;
    str_list->flags = (int*)calloc(NUM_OF_FLAGS, sizeof(int));
    str_list->file_link = NULL;
    str_list->tab_width = 4;
    signal(SIGWINCH, chg_size);
    if (argc == 2)
    {
        fd = fopen(argv[1], "r");
        if (fd == NULL)
            fd = fopen(argv[1], "w");
        file = (char*)malloc(sizeof(char) * (strlen(argv[1]) + 1));
        while (argv[1][k])
        {
            file[k] = argv[1][k];
            k++;
        }
        file[k] = '\0';
        str_list->file_link = file;
        str_list->flags[F_OPEN] = 1;
        make_list(str_list, fd);
    }
    else
        ft_putstr("Too many or no arguments\n");
    //help_init();
}

int     main(int argc, char **argv)
{
    char        *buf;
    t_cmd_list  *cmd;
    int         r;
    int         i;
    int         size;
    int         ch;

    init(argv, argc);
    while (str_list->flags[F_CHANGED] || str_list->flags[F_EXIT] == 0)
    {
        ft_putstr("Editor:");
        size = 0;
        //i = 0;
        buf = (char*)malloc(sizeof(char));
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
            size++;
            buf = realloc(buf, sizeof(char) * (size + 1));
            buf[size-1] = ch;
        }
        if (ch == EOF)
            ft_putchar('\n');
        buf[size] = '\0';
        cmd = (t_cmd_list*)malloc(sizeof(t_cmd_list));
        cmd_template(buf, cmd);
        free(buf);
        /*printf("name: %s\n", cmd->key_word);
        if (cmd->params)
            while (cmd->params[i])
            {
                printf("the %d argument: %s\n", i, cmd->params[i]);
                i++;
            }*/
        i = 0;
        r = 0;
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
                r = editor_write(cmd, str_list);
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
            case HELP_NUM:
                //str_list->flags[F_PRINT] = 1;
                help_func();
                //str_list->flags[F_PRINT] = 0;
                break;
            default:
                ft_putstr("Wrong command, type 'help' for more information\n");
        }
        if (r)
            err_check(r);
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
    //list_free(help_list);
    //printf("r = %i\n", r);
    return 0;
}
