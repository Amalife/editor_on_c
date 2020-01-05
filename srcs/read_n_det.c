#include "std_n_def.h"
#include "func_pro.h"
#include "global.h"

char        *g_cmd_base[NUM_OF_CMD] = {"exit", "read", "open", "write",
                                        "print", "set", "insert", "edit", 
                                                "replace", "delete", "help"};

int     check_last(char *str, int k)
{
    while (str[k] && (str[k] == ' ' || str[k] == '\t'))
        k++;
    if (str[k] == '\0')
        return 0;
    else
        return 1;
}

char    *quote_str(char *str, int k)
{
    char    *buf;
    int     i;

    i = 0;
    buf = (char*)malloc(sizeof(char) * 3);
    if (str[k] == '"' && str[k+1] == '"' && str[k+2] == '"')
    {
        buf = realloc(buf, sizeof(char) * 4);
        while (i != 3)
        {
            buf[i] = str[k];
            i++;
            k++;
        }
        buf[i] = '\0';
        return buf;
    }
    buf[i] = str[k];
    i++;
    k++;
    while ((str[k-1] == '\\' || str[k] != '"') && str[k])
    {
        buf = realloc(buf, sizeof(char) * (i + 3));
        buf[i] = str[k];
        i++;
        k++;
    }
    buf[i] = str[k];
    i++;
    buf[i] = '\0';
    return buf;
}

char    *sim_str(char *str, int k)
{
    char    *buf;
    int     i;

    i = 0;
    buf = (char*)malloc(sizeof(char) * 2);
    while (str[k] != ' ' && str[k] != '\t' && str[k])
    {
        buf = realloc(buf, sizeof(char) * (i + 2));
        buf[i] = str[k];
        i++;
        k++;
    }
    buf[i] = '\0';
    return buf;
}

char    *make_str(char *str, int k)
{
    char *buf;

    if (str[k] == '"')
        buf = quote_str(str, k);
    else if (str[k] != ' ' && str[k] != '\t')
        buf = sim_str(str, k);
    return buf;
}

void    cmd_template(char *str, t_cmd_list *cmd)
{
    int k;

    k = 0;
    cmd->num_par = 0;
    while (str[k] && (str[k] == ' ' || str[k] == '\t'))
        k++;
    cmd->key_word = make_str(str, k);
    k += strlen(cmd->key_word);
    cmd->params = (char**)malloc(sizeof(char*));
    while (str[k] && check_last(str, k))
    {
        while (str[k] && (str[k] == ' ' || str[k] == '\t'))
            k++;
        cmd->params = realloc(cmd->params, sizeof(char*) * (cmd->num_par + 2));
        cmd->params[cmd->num_par] = make_str(str, k);
        k += strlen(cmd->params[cmd->num_par]);
        cmd->num_par++;
    }
    cmd->params[cmd->num_par] = NULL;
}

int     read_n_det(t_cmd_list *cmd)
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
