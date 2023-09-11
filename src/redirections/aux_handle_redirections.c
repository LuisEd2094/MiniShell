#include "redirections_internal.h"
/*
char   *get_file_name(char *input, int *i)
{
    char    *new;
    int     j;
    int     k;

    j = get_arg_size_skip_redirections(input);
    new = (char *)malloc(sizeof(char) * j + 1);
    if (!new)
        return(NULL);
    ft_strlcpy(new, input, j + 1);
        *i += j;
    return(new);

}

int get_starting_pos(char *input)
{
    int i;

    if (input[1] && input[1] == input[0])
        i = 2;
    else
        i = 1;
    i += get_white_space_size(&input[i]);
    return (i);
}
*/



int get_redir_type(char *input)
{
    if (input[1] && input[0] == '>' && input[1] == '>')
        return (APPEND_OUTPUT);
    else if (input[0] == '>')
        return (OUTPUT_REDIRECT);
    else if (input[1] && input[0] == '<' && input[1] == '<')
        return (HERE_DOCUMENT);
    else
        return (INPUT_REDIRECT);
}
