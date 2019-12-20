#include "std_n_def.h"
#include "func_pro.h"
#include "global.h"

char        *g_cmd_base[NUM_OF_CMD] = {"exit", "read", "open", "write",
                                        "print", "set", "insert", "edit", 
                                                "replace", "delete", "help"};

int         ft_count_sp(char *str, int k)
{
    int n;

    n = 0;
    while (str[k])
    {
        if (str[k] == ' ' || str[k] == '\t' || str[k] == '"')
            n++;
        k++;
    }
    return n;
}

int         ft_strlen_sp(char *str, int k)
{
    while (str[k] != ' ' && str[k] != '\t' && str[k])
        k++;
    return k;
}

int         count_quotes(char *str, int k)
{
    int n;

    n = 1;
    k++;
    while (str[k])
    {
        if (str[k] == '"' && (str[k+1] == ' ' || str[k+1] == '\t' || 
                                                        str[k+1] == '\0'))
            break;
        k++;
        n++;
    }
    n++;
    return n;
}

char        *quote_str(char *str, int k)
{
    char    *buf;
    int     i;
    int     t;

    i = 0;
    t = count_quotes(str,k);
    buf = (char*)malloc(sizeof(char) * (t + 2));
    do
    {
        buf[i] = str[k];
        i++;
        k++;
    } while ((str[k] != '"' || (str[k+1] != ' ' && str[k+1] != '\t')) && str[k]);
    if (str[k])
    {
        buf[i] = '"';
        i++;
    }
    buf[i] = '\0';
    return buf;
}

t_cmd_list  *ft_cmd_template(char *str)
{
    t_cmd_list  *cmd;
    int         k;
    int         i;

    k = 0;
    cmd = (t_cmd_list*)malloc(sizeof(t_cmd_list));
    k = ft_space(str, k);
    i = k;
    cmd->key_word = (char*)malloc(sizeof(char) * (ft_strlen_sp(str, k) - i + 1));
    i = 0;
    while (str[k] != ' ' && str[k] != '\t' && str[k])
    {
        cmd->key_word[i] = str[k];
        i++;
        k++;
    }
    cmd->key_word[i] = '\0';
    cmd->params = ft_split_whitespaces(str);
    return cmd;
}

char        **ft_split_whitespaces(char *str)
{
    char    **buf;
    int     i;
    int     j;
    int     k;

    k = 0;
    k = ft_space(str, k);
    if (ft_count_sp(str, k) == 0)
        return NULL;
    buf = (char**)malloc(sizeof(char*) * ft_count_sp(str, k) + 1);
    i = 0;
    j = 0;
    while (str[k] != ' ' && str[k] != '\t' && str[k])
        k++;
    while (str[k])
    {
        k = ft_space(str, k);
        if (str[k] == '"')
        {
            buf[i] = quote_str(str, k);
            k += count_quotes(str, k);
        }
        else if (str[k]) 
        {
            j = k;
            buf[i] = (char*)malloc(sizeof(char) * (ft_strlen_sp(str, k) - j + 1));
            j = 0;
            while (str[k] != ' ' && str[k] != '\t' && str[k])
            {
                buf[i][j] = str[k];
                j++;
                k++;
            }
            buf[i][j] = '\0';
            j = 0;
        }
        i++;
    }
    buf[i] = NULL;
    return buf;
}

int         read_n_det(t_cmd_list *cmd)
{
    int i;

    i = 0;
    while (i < NUM_OF_CMD)
    {
        if (strcmp(cmd->key_word, g_cmd_base[i]) == 0)
            return i;
        i++;
    }
    return -1;
}
