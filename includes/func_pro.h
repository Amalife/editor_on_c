#ifndef __FUNC_PRO_H__
# define __FUNC_PRO_H__

#include "global.h"

char        **ft_split_whitespaces(char *str);
void        ft_putchar(char c);
void        ft_putstr(char *str);
int         ft_space(char *str, int k);
int         ft_strlen(char *str);
t_cmd_list  *ft_cmd_template(char *str);
int         editor_exit(char **params, t_doub_list *str_list);
int         editor_read_n_open(char **params, t_doub_list *str_list);
char        *read_file(FILE *fd);
int         read_n_det(t_cmd_list *cmd);
int         ft_strlen_news(char *str, int cur);
int         ft_strlen_sp(char *str, int k);
int         ft_count_news(char *str);
int         ft_count_sp(char *str, int k);
void        list_free(t_doub_list *str_list);
int         add_to_list(char *buf, t_doub_list *str_list, int c, int i);
int         make_list(t_doub_list *str_list, FILE *fd);
int         print(char **params, t_doub_list *str_list);
void        ft_putnstr(t_node *head, int n, int ws_col, int tabwidth, int c, 
                                                                        int fl);
int         keys(t_doub_list *str_list);
int         set_func(char **params, t_doub_list *str_list);
void        ft_putnbr(int num);
int         ft_numcsize(int str_count);
void        ft_sp_num(int num, int sp);
int         ft_atoi(char *str);
int         count_quotes(char *str, int k);
char        *quote_str(char *str, int k);
int         insert_func(char **params, t_doub_list *str_list);
int         add_new_str(t_doub_list *str_list, int str_num, char *params);
char        *unqouting(char *str);
int         check_quotes(char *str);
int         check_sp_sym(char *str);
char        *sp_sym_handler(char *str, t_doub_list *str_list, int str_num);
void        ft_putstrnw(t_node *head, int c, int tabwidth, int fl);
int         insert_group(t_doub_list *str_list, int str_num);

#endif
