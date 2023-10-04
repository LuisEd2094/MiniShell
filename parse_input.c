#include <libft.h>
#include <stdbool.h>


typedef struct s_input
{
    char    quote;
    bool    pipe;
    bool    left_of_pipe;
    bool    redirections;
}   t_input;

void init_checker(t_input *checker)
{
    checker->quote = 0;
    checker->left_of_pipe = 0;
    checker->pipe = 0;
    checker->redirections = 0;
}

bool    check_vals(t_input *checker)
{
    return (checker->quote || !checker->left_of_pipe || checker->pipe);
}

bool    parse_input(char *input)
{
    t_input checker;
    int     i;
    char    quote;

    init_checker(&checker);
    i = 0;
    while (input[i])
    {
        if (!checker.left_of_pipe && !ft_isspace(input[i]) && input[i] != '|')
            checker.left_of_pipe = 1;
        if (!checker.quote && (input [i] == '\'' || input[i] == '"'))
            checker.quote = input[i];
        else if (checker.quote)
        {
            if (input[i] == checker.quote)
                checker.quote = 0;
        }
        else if (!checker.pipe && input[i] == '|')
        {
            if (!checker.left_of_pipe)
                return (1);
            checker.pipe = 1;
        }
        else if (checker.pipe)
        {
            if (input[i] == '|')
                return (1);
            if (!ft_isspace(input[i]))
                checker.pipe = 0;
        }
        i++;
    }
    return check_vals(&checker);
}
