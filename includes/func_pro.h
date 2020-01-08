#ifndef __FUNC_PRO_H__
# define __FUNC_PRO_H__

#include "global.h"

void    ft_putchar(char c);
void    ft_putstr(char *str);
void    ft_putnbr(int num);
int     ft_atoi(char *str);
char    *ft_strcat(char *dest, char *app);

void    cmd_template(char *str, t_cmd_list *cmd);
int     check_last(char *str, int k);
char    *quote_str(char *str, int k);
char    *sim_str(char *str, int k);
char    *make_str(char *str, int k);
int     read_n_det(t_cmd_list *cmd);
void    help_func();
void    err_check(int r);

int     editor_exit(t_cmd_list *cmd, t_doub_list *str_list);
int     editor_read_n_open(t_cmd_list *cmd, t_doub_list *str_list);
int     editor_write(t_cmd_list *cmd, t_doub_list *str_list);
char    *read_file(FILE *fd);
int     make_list(t_doub_list *str_list, FILE *fd);
char    *unquoting(char *str);
int     add_to_list(char *buf, t_doub_list *str_list);
void    list_free(t_doub_list *str_list);

int     print(t_cmd_list *cmd, t_doub_list *str_list);
void    ft_putnstr(t_node *head, int n, int ws_col, int tabwidth, int c, int fl);
void    chg_size();
void    print_strs(t_doub_list *str_list, struct winsize wz, int t);
int     keys(t_doub_list *str_list);
int     ft_numcsize(int str_count);
void    ft_sp_num(int num, int sp);
void    ft_putstrnw(t_node *head, int c, int tabwidth, int fl);

int     set_func(t_cmd_list *cmd, t_doub_list *str_list);

int     insert_func(t_cmd_list *cmd, t_doub_list *str_list);
int     add_new_str(t_doub_list *str_list, char *str);
int     insert_str(t_doub_list *str_list, char *str);
int     check_quotes(char *str);
char    *sp_sym_handler(char *str);
int     insert_group(t_doub_list *str_list);
int     insert_sym(t_doub_list *str_list, char **params);

int     edit_func(t_cmd_list *cmd, t_doub_list *str_list);

int     replace_func(t_cmd_list *cmd, t_doub_list *str_list);
char    *place_str(char *sample, char *str_add, char *str);
int     replace_string(t_doub_list *str_list, char *new_str);

int     delete_func(t_cmd_list *cmd, t_doub_list *str_list);
void    delete_node(t_doub_list *str_list, int str_num);
int     com_handler(t_doub_list *str_list, char *com_type);
void    delete_pascal(t_doub_list *str_list);
void    delete_c(t_doub_list *str_list);
void    delete_cpp(t_doub_list *str_list);
void    delete_shell(t_doub_list *str_list);
char    *com_str(char sym);
char    *block_com_str(char sym);

#endif
