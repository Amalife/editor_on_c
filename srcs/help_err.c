#include "std_n_def.h"
#include "func_pro.h"
#include "global.h"

//t_doub_list *help_list;
//t_cmd_list  *cmd_help;
//int         str_num;

void    help_func()
{
    /*help_list = (t_doub_list*)malloc(sizeof(t_doub_list));
    help_list->tail = NULL;
    help_list->head = NULL;
    help_list->flags = (int*)calloc(NUM_OF_FLAGS, sizeof(int));
    help_list->file_link = NULL;
    help_list->tab_width = 4;
    str_num = 0;*/
    ft_putstr("\t\t\t\t\t_____ZASHODAKTOR_HELP_____\t\t\t\t\t");
	ft_putstr("\n\n\n\t\t\t___Group of text viewing commands___\t\t\t");
    ft_putstr("\n\n\tset wrap [yes/no]\t\t\t\tSwitches the display mode between \"long lines are wraped\" and \"long lines continue\"");
	ft_putstr("\n\tset numbers [yes/no]\t\t\t\tTurns on/off the numbers of strings");
	ft_putstr("\n\tset tabwidth [X]\t\t\t\tChanges tab width to X value. X must be more than 0");
	ft_putstr("\n\tprint pages\t\t\t\t\tScreen view of the entire text page by page.\n\t\t\t\t\t\t\t\tNext page - 'space', exit the screen view - 'q'. In \"long lines continue\" mode '<' and '>' moves strings to the left or right");
	ft_putstr("\n\tprint range [X] [Y]\t\t\t\tLike print pages, but screen view of the range of strings from X to Y. X must be less or equal than Y and Y can't be out of the strings range.\n\t\t\t\t\t\t\t\tIf there is no Y, then screen view from X to the end of the entire text");
	ft_putstr("\n\n\t\t\t___Group of insert string commands___\t\t\t");
	ft_putstr("\n\n\tinsert after [X] \"string\"\t\t\tInserts a string or group of strings after the X row. String must be in double quotes. If X = 0, inserts to the begining of text.\n\t\t\t\t\t\t\t\tTo insert a group of strings, which begin and end with three consecutive double quotes.");
	ft_putstr("\n\n\t\t\t___Group of line editing commands___\t\t\t");
	ft_putstr("\n\n\tedit string [X] [Y] [Z]\t\t\t\tReplaces the character to Z character in the X line, starting from the Y position. X and Y can't be out of range");
	ft_putstr("\n\tinsert symbol [X] [Y] [Z]\t\t\tIs similar to edit string, but it inserts a character at the position.\n\t\t\t\t\t\t\t\tIf there is a out of range to the right, then insert at the end, to the left - to the beginning");
	ft_putstr("\n\treplace substring [X] [Y] \"sample\" \"string\"\tSearches and replaces \"sample\" substrings to \"string\" in a range of strings.\n\t\t\t\t\t\t\t\tRange rule like in the 'print range'. Strings must be in double quotes.\n\t\t\t\t\t\t\t\tIf \"sample\" is '^', then assigns to the beginning of the each string, if '$', then at the end");
	ft_putstr("\n\tdelete range [X] [Y]\t\t\t\tDeletes strings in a range of strings. Range rule like in the 'print range'");
	ft_putstr("\n\tdelete comments [comment_type]\t\t\tDeletes all comments in the entire text. If comment_type is 'pascal', then delete all comments PASCAL. If 'c',then delete all comments C.\n\t\t\t\t\t\t\t\tIf 'c++', then delete all comments C++, not deleting C comments. If 'shell', then delete all comments Shell");
	ft_putstr("\n\n\t\t\t___Group of tech commands___\t\t\t");
	ft_putstr("\n\n\texit\t\t\t\t\t\tExits the text editor, to exit hard, then type 'exit force'");
	ft_putstr("\n\topen\t\t\t\t\t\tOpens file");
    ft_putstr("\n\tread\t\t\t\t\t\tOpens file and copy all strings from it, but don't save filepath");
	ft_putstr("\n\twrite\t\t\t\t\t\tIf there is a filepath saves the file, unless type 'write \"filepath\"'");
	ft_putstr("\n\tset name \"filepath\"\t\t\t\tChanges the filepath of opened file to \"filepath\". If typed without \"filepath\", then delete the current filepath");
	ft_putstr("\n\thelp\t\t\t\t\t\tViews information of commands of that editor\n");
	//cmd_help->key_word = "print";
	//cmd_help->params[0] = "pages";
	//cmd_help->num_par = 1;
}

void    err_check(int r)
{
    if (r == PARAMS_ERR)
        ft_putstr("Wrong parameters, type 'help' for more information\n");
    else if (r == OPEN_FILE_ERR)
        ft_putstr("Failed open file\n");
    else if (r == LIST_ADD_ERR)
        ft_putstr("Failed add string to list\n");
    else if (r == NOT_SAVED)
        ft_putstr("The file isn't saved\n");
    else if (r == STDIN_ERR)
        ft_putstr("Wrong input\n");
    else if (r == TAB_ERR)
        ft_putstr("Tab width must be more than 0\n");
    else if (r == STR_COUNT_ERR)
        ft_putstr("Out of range of strings\n");
    else if (r == NO_FILE_ERR)
        ft_putstr("There is no opened file\n");
    else if (r == SP_SYM_ERR)
        ft_putstr("It is not a special symbol\n");
    else if (r == NO_FILE_LINK)
        ft_putstr("There is no file link\n");
}
