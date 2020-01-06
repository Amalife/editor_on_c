#ifndef __FUNC_PRO_H__
# define __FUNC_PRO_H__

#include "global.h"

void    ft_putchar(char c);
void    ft_putstr(char *str);
void    ft_putnbr(int num);
int     ft_atoi(char *str);

void    cmd_template(char *str, t_cmd_list *cmd);
int     check_last(char *str, int k);
char    *quote_str(char *str, int k);
char    *sim_str(char *str, int k);
char    *make_str(char *str, int k);
int     read_n_det(t_cmd_list *cmd);

int     editor_exit(t_cmd_list *cmd, t_doub_list *str_list);
int     editor_read_n_open(t_cmd_list *cmd, t_doub_list *str_list);
char    *read_file(FILE *fd);
int     make_list(t_doub_list *str_list, FILE *fd);
char    *unqouting(char *str);
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

int     replace_func(char **params, t_doub_list *str_list);
void    check_str(char *sample, char *add_str, t_node *head);
char    *place_str(char *add_str, t_node *head, int k);
char    *ft_strcat(char *dest, char *src);

int     delete_func(t_cmd_list *cmd, t_doub_list *str_list);
void    delete_node(t_doub_list *cmd, int str_num);
#endif
