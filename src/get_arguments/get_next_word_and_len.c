#include "execute_internal.h"

int get_next_word_len(char *cmd)
{
    int len;

    len = 0;
    while (cmd[len] && cmd[len] != '"' && !ft_isspace(cmd[len]) \
        && cmd[len] != '<' && cmd[len] != '>' && cmd[len] != '$')
        len++;
    return (len);
}


char *get_next_word(char *cmd)
{
    int len;

    len = get_next_word_len(cmd);
    return (ft_substr(cmd, 0, len));
}