#include <libft.h>
#include <stdbool.h>


typedef struct s_input
{
    char    quote;
    char    redir_token;
    int     redir_pos;
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
    checker->redir_token = 0;
}

int    check_vals(t_input *checker)
{
    if (checker->quote)
        return (1); //print custom msg
    if (checker->pipe)
        return (1); //custom msg
    if (checker->redirections)
        return (258); //new line
    return (0);
}


 /// 258 == unexpected token 
int    parse_input(char *input)
{
    t_input checker;
    int     i;

    init_checker(&checker);
    i = -1;
    while (input[++i])
    {
        if (ft_isspace(input[i]))
               continue;
        if (!checker.redirections && !checker.quote && (input[i] == '>' || input[i] == '<'))
        {
            checker.redirections = 1;
            checker.redir_token = input[i];
            checker.redir_pos = i;
        }
        else if (checker.redirections)
        {
            if (input[checker.redir_pos + 1] && input[checker.redir_pos] == input[checker.redir_pos + 1] && \
            ((input[i] == '>' || input[i] == '<') && i != checker.redir_pos + 1))
                return(258);
            if (i == checker.redir_pos + 1 && (input[i] == '|' || (input[i] == '>' || input[i] == '<')))
            {
                if (checker.redir_token == '>' && input[i] == '<')
                    return(258);
                continue;
            }
            else
            {
                if (input[i] == '>' || input[i] == '<')
                    return(258);
            }
            if (input[i] !=  '|')
                checker.redirections = 0;
        }
        if (!checker.left_of_pipe && input[i] != '|')
            checker.left_of_pipe = 1;
        if (!checker.quote && (input [i] == '\'' || input[i] == '"'))
            checker.quote = input[i];
        else if (checker.quote)
        {
            if (input[i] == checker.quote)
                checker.quote = 0;
        }
        if (!checker.pipe && input[i] == '|')
        {
            if (!checker.left_of_pipe)
                return (258);
            checker.pipe = 1;
        }
        else if (checker.pipe)
        {
            if (input[i] == '|')
                return (258);
            checker.pipe = 0;
        }
    }
    return check_vals(&checker);
}
