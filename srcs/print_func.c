#include "std_n_def.h"
#include "global.h"
#include "func_pro.h"

void    ft_putnstr(t_node *head, int n, int ws_col, int tabwidth,
                                                        int c, int fl)
{
    int col;
    int count;
    
    col = 0;
    count = tabwidth;
    if (n >= head->width)
        ft_putchar('\n');
    else
        while (col < (ws_col - c - 1) && head->str[n])
        {
            if (head->str[n] == '\t')
            {
                while (count)
                {
                    ft_putchar(' ');
                    count--;
                }
                n++;
                col += tabwidth;
                count = tabwidth;
            }
            else
            {
                ft_putchar(head->str[n]);
                if (head->str[n] == '\r')
                {
                    if (fl)
                        ft_sp_num(head->num, c);
                    else
                        ft_putchar('~');
                }
                n++;
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

int     print(char **params, t_doub_list *str_list)
{
    struct termios  old_term;
    struct termios  new_term;
    struct winsize  wz;
    int             row;
    t_node          *save;
    t_node          *save_str;
    int             f;
    int             n;
    int             top_width;
    int             c;
    int             k;
    int             t;

    save = str_list->head;
    t = 0;
    if (strcmp(params[0], "range") == 0)
    {
        if (params[1] && params[2] && ft_atoi(params[1]) > 0)
        {
            if (ft_atoi(params[1]) > ft_atoi(params[2]))
                return PARAMS_ERR;
            t = ft_atoi(params[1]);
            if (t > str_list->str_count)
                return PARAMS_ERR;
            while (t != str_list->head->num)
                str_list->head = str_list->head->next;
            t = ft_atoi(params[2]);
            if (t > str_list->str_count)
                return PARAMS_ERR;
        }
        else if (params[1])
        {
            if (ft_atoi(params[1]) <= 0)
                return PARAMS_ERR;
            t = ft_atoi(params[1]);
            if (t > str_list->str_count)
                return PARAMS_ERR;
            while (t != str_list->head->num)
                str_list->head = str_list->head->next;
            t = 0;
        }
    }
    else if (strcmp(params[0], "pages"))
        return PARAMS_ERR;
    if (!isatty(STDIN_FILENO))
    {
        ft_putstr("Not a standard input\n");
        return STDIN_ERR;
    }
    n = 0;
    row = 0;
    f = 0;
    c = 0;
    k = 0;
    tcgetattr(STDIN_FILENO, &old_term);
    memcpy(&new_term, &old_term, sizeof(struct termios));
    new_term.c_lflag &= ~(ECHO | ICANON);
    new_term.c_cc[VMIN] = 1;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_term);
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &wz);
    top_width = wz.ws_col;
    if (str_list->flags[F_NUM])
        c = ft_numcsize(str_list->str_count);
    do
    {
        if (f == P_RIGHT)
        {
            str_list->head = save_str;
            if (n < (top_width - wz.ws_col + c) && (top_width - wz.ws_col))
                n++;
        }
        else if (f == P_LEFT)
        {
            str_list->head = save_str;
            if (n)
                n--;
        }
        if (f != P_NONE)
        {
            if (f == P_DOWN)
            {
                top_width = wz.ws_col;
                n = 0;
            }
            save_str = str_list->head;
            ft_putchar('\n');
            while (row < (wz.ws_row - 1) && str_list->head)
            {
                if (str_list->head->width > top_width)
                    top_width = str_list->head->width;
                if (str_list->flags[F_NUM])
                    ft_sp_num(str_list->head->num, c);
                else
                    ft_putchar('~');
                if (str_list->flags[F_NO_WRAP])
                {
                    k = str_list->head->width / wz.ws_col;
                    ft_putstrnw(str_list->head, c, str_list->tab_width,
                                                str_list->flags[F_NUM]);
                }
                else
                    ft_putnstr(str_list->head, n, wz.ws_col, 
                                str_list->tab_width, c, str_list->flags[F_NUM]);
                if (t == str_list->head->num)
                {
                    str_list->head = NULL;
                    row++;
                    break;
                }
                str_list->head = str_list->head->next;
                row += (k + 1);
            }
            while (row < (wz.ws_row - 1))
            {
                ft_putchar('\n');
                row++;
            }
            row = 0;
            ft_putstr("<press 'q' to exit>");
        }
        f = keys(str_list);
    } while (f);
    ft_putchar('\n');
    str_list->head = save;
    tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
    return 0;
}
