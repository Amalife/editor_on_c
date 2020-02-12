#include "std_n_def.h"
#include "global.h"
#include "func_pro.h"

t_doub_list     *str_list;
t_node          *f_save;
t_node          *save;
int             fl_print;
struct winsize  wz;
int             rng;
int             cur_pos;
int             start;
int             top_width;

void    ft_putnstr(t_node *head, int cur_pos, int ws_col, int tabwidth,
                                                        int c, int fl)
{
    int col;
    int count;
    
    col = 0;
    count = tabwidth;
    if (cur_pos >= head->width)
        ft_putchar('\n');
    else
        while (col < (ws_col - c - 1) && head->str[cur_pos])
        {
            if (head->str[cur_pos] == '\t')
            {
                while (count)
                {
                    ft_putchar(' ');
                    count--;
                }
                cur_pos++;
                col += tabwidth;
                count = tabwidth;
            }
            else
            {
                ft_putchar(head->str[cur_pos]);
                if (head->str[cur_pos] == '\r')
                {
                    if (fl)
                        ft_sp_num(head->num, c);
                    else
                        ft_putchar('~');
                }
                cur_pos++;
                col++;
            }
        }
}

void    ft_putstrnw(t_node *head, int c, int tabwidth, int fl)
{
    int i;
    int count;

    i = 0;
    count = tabwidth;
    while (head->str[i])
    {
        if (head->str[i] == '\t')
        {
            while (count)
            {
                ft_putchar(' ');
                count--;
            }
            i++;
            count = tabwidth;
        }
        else
        {
            ft_putchar(head->str[i]);
            if (head->str[i] == '\r')
            {
                if (fl)
                    ft_sp_num(head->num, c);
                else
                    ft_putchar('~');
            }
            i++;
        }
    }
}

void    ft_putnbr(int num)
{
    if (num >= 10)
        ft_putnbr(num / 10);
    ft_putchar(num % 10 + '0');
}

int     ft_numcsize(int str_count)
{
    int i;

    i = 0;
    while (str_count /= 10)
        i++;
    i++;
    return i;
}

void    ft_sp_num(int num, int sp)
{
    int i;
    int k;
    
    k = num;
    i = 0;
    while (k /= 10)
        i++;
    i++;
    sp -= i;
    while (sp)
    {
        ft_putchar(' ');
        sp--;
    }
    ft_putnbr(num);
    ft_putchar(' ');
}

int     keys(t_doub_list *str_list)
{
    char    ch;

    ch = getchar();
    //printf("\n%c\n", ch);
    if ((ch != 'q') && (str_list->head || ch != ' '))
    {
        if (ch == ' ')
            return P_DOWN;
        else if (ch == '.')
            return P_RIGHT;
        else if (ch == ',')
            return P_LEFT;
        else
            return P_NONE;
    }
    else
        return P_QUIT;

}

void chg_size()
{
    if (str_list->flags[F_PRINT])
    {
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &wz);
        str_list->flags[F_SIG] = 1;
        str_list->head = save;
        ft_putstr("\e[2J\e[3J\e[r");
        print_strs(str_list, wz, rng);
    }
}

void    print_strs(t_doub_list *str_list, struct winsize wz, int rng)
{
    int row;
    int k;
    
    row = 0;
    k = 0;

    save = str_list->head;
    ft_putchar('\n');
    while (row < (wz.ws_row - 1) && str_list->head)
    {
        if (str_list->head->width > top_width)
            top_width = str_list->head->width;
        if (str_list->flags[F_NUM])
            ft_sp_num(str_list->head->num, start);
        else
            ft_putchar('~');
        if (str_list->flags[F_NO_WRAP])
        {
            k = str_list->head->width / wz.ws_col;
            ft_putstrnw(str_list->head, start, str_list->tab_width,
                                        str_list->flags[F_NUM]);
        }
        else
            ft_putnstr(str_list->head, cur_pos, wz.ws_col, 
                        str_list->tab_width, start, str_list->flags[F_NUM]);
        if (rng == str_list->head->num)
        {
            str_list->head = NULL;
            row++;
            break;
        }
        str_list->head = str_list->head->next;
        f_save = str_list->head;
        row += (k + 1);
    }
    while (row < (wz.ws_row - 1))
    {
        ft_putchar('\n');
        row++;
    }
    row = 0;
    ft_putstr("<press 'q' to exit>");
    if (str_list->flags[F_SIG])
    {
        str_list->head = save;
        str_list->flags[F_SIG] = 0;
    }
}

int     print(t_cmd_list *cmd, t_doub_list *str_list)
{
    t_node          *save_str = NULL;
    struct termios  old_term;
    struct termios  new_term;
    t_node          *sp_save;

    sp_save = str_list->head;
    f_save = str_list->head;
    //g_str_list = str_list;
    fl_print = 0;
    rng = 0;
    start = 0;
    top_width = 0;
    cur_pos = 0;
    if (str_list->flags[F_FILE] == 0)
        return NO_FILE_ERR;
    if (cmd->num_par == 0 || cmd->num_par > 3)
        return PARAMS_ERR;
    if (strcmp(cmd->params[0], "range") == 0)
    {
        if (cmd->num_par == 3 && ft_atoi(cmd->params[1]) > 0)
        {
            if (ft_atoi(cmd->params[1]) > ft_atoi(cmd->params[2]))
                return PARAMS_ERR;
            if (ft_atoi(cmd->params[1]) > str_list->str_count || 
                                ft_atoi(cmd->params[2]) > str_list->str_count)
                return STR_COUNT_ERR;
            rng = ft_atoi(cmd->params[1]);
            while (rng != str_list->head->num)
                str_list->head = str_list->head->next;
            rng = ft_atoi(cmd->params[2]);
        }
        else if (cmd->num_par == 2)
        {
            if (ft_atoi(cmd->params[1]) <= 0)
                return PARAMS_ERR;
            rng = ft_atoi(cmd->params[1]);
            if (rng > str_list->str_count)
                return PARAMS_ERR;
            while (rng != str_list->head->num)
                str_list->head = str_list->head->next;
            rng = 0;
        }
        else
            return PARAMS_ERR;
    }
    else if (strcmp(cmd->params[0], "pages") || cmd->num_par > 1)
        return PARAMS_ERR;
    if (!isatty(STDIN_FILENO))
    {
        ft_putstr("Not a standard input\n");
        return STDIN_ERR;
    }
    tcgetattr(STDIN_FILENO, &old_term);
    memcpy(&new_term, &old_term, sizeof(struct termios));
    new_term.c_lflag &= ~(ECHO | ICANON);
    new_term.c_cc[VMIN] = 1;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wz);
    top_width = wz.ws_col;
    if (str_list->flags[F_NUM])
        start = ft_numcsize(str_list->str_count);
    do
    {
        if (fl_print == P_RIGHT)
        {
            str_list->head = save_str;
            if (cur_pos < (start + top_width - wz.ws_col) && (top_width - wz.ws_col))
                cur_pos++;
        }
        else if (fl_print == P_LEFT)
        {
            str_list->head = save_str;
            if (cur_pos)
                cur_pos--;
        }
        if (fl_print != P_NONE)
        {
            if (fl_print == P_DOWN)
            {
                top_width = wz.ws_col;
                cur_pos = 0;
                str_list->head = f_save;
            }
            save_str = str_list->head;
            ft_putstr("\e[2J\e[3J\e[r");
            print_strs(str_list, wz, rng);
            fl_print = keys(str_list);
            //printf("\n%i\n", fl_print);
        }
        else
            fl_print = keys(str_list);
    } while (fl_print);
    ft_putchar('\n');
    str_list->head = sp_save;
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
    return 0;
}
