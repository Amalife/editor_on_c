#ifndef __GLOBAL_H__
# define __GLOBAL_H__

enum            e_print
{
    P_QUIT,
    P_DOWN,
    P_RIGHT,
    P_LEFT,
    P_NONE
};

enum            e_cmd_list
{
    EXIT_NUM,
    READ_NUM,
    OPEN_NUM,
    WRITE_NUM,
    PRINT_NUM,
    SET_NUM,
    INSERT_NUM,
    EDIT_NUM,
    REPLACE_NUM,
    DELETE_NUM,
    HELP_NUM
};

enum            e_err_list
{
    PARAMS_ERR = -20,
    OPEN_FILE_ERR,
    LIST_ADD_ERR,
    NOT_SAVED,
    STDIN_ERR,
    TAB_ERR,
    STR_COUNT_ERR,
    NO_FILE_ERR
};

enum            e_flags
{
    F_EXIT,
    F_CHANGED,
    F_OPEN,
    F_NUM,
    F_NO_WRAP,
    F_SIG,
    F_PRINT,
    F_FILE
};

typedef struct  s_cmd_list
{
    char    *key_word;
    char    **params;
    int     num_par;
}               t_cmd_list;

typedef struct  s_node
{
    char            *str;
    struct  s_node  *prev;
    struct  s_node  *next;
    int             num;
    int             width;
}               t_node;

typedef struct  s_doub_list
{
    t_node  *head;
    t_node  *tail;
    char    *file_link;
    int     *flags;
    int     str_count;
    int     tab_width;
}               t_doub_list;

#endif
