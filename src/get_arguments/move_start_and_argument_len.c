#include "execute_internal.h"

int get_argument_len(char *cmd)
{
    int i; 

    i = 0;
    if (cmd[i] == '\'' || cmd[i] == '"')
    {
        i = get_quotes_size(cmd);
        i -= 2;
    } 
    else
        i = get_arg_size_skip_redirections(cmd);
    return (i);

}

int move_start(char *cmd)
{
    int i;

    i = 0;
    if (cmd[i] == '<' || cmd[i] == '>')
        return (get_redirection_size(&cmd[i]));
    else if (cmd[i] == '"' || cmd[i] == '\'')
        return(get_quotes_size(cmd));
    else
        return (get_argument_len(&cmd[i]));
}


