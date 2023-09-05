#include "execute_internal.h"

int add_size_of_pipe(char *input, int * i)
{
    if (input[0] == '|')
    {
        *i += 1;
        return (1);
    }
    return (0);
}


int    get_quotes_size(char *input)
{
    char    quote;
    int     i;
    
    i = 0;
    quote = input[i];
    i++;
    while(input[i] && input[i] != quote)
        i++;
    i++;
    return(i);
}

int get_white_space_size(char *input)
{
    int i;

    i = 0;
    while(input[i] && ft_isspace(input[i]))
        i++;
    return (i);
}

int get_arg_size_skip_redirections(char *input)
{
    int i;

    i = 0;
    while (input[i] && ft_isascii(input[i]) && !ft_isspace(input[i]) \
    && (input[i] != '<' && input[i] != '>'))
        i++;
    return (i);
}

int    get_redirection_size(char *input)
{
    int     i;
    char    symbol;

    i = 0;
    symbol = input[i];
    if (input[i + 1] && input[i + 1] == symbol)
        i += 2;
    else
        i++;
    return (i); 
}

