#include "redirections_internal.h"

int get_redir_type(char *input)
{
    if (input[1] && input[0] == '>' && input[1] == '>')
        return (APPEND_OUTPUT);
    else if (input[0] == '>')
        return (OUTPUT_REDIRECT);
    else
        return (INPUT_REDIRECT);
}
