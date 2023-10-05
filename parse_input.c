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

    return (checker->pipe);
}


 /// 258 == unexpected token 
int    parse_input(char *input)
{
    t_input checker;
    int     i;

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
                return (258); // return error
            checker.pipe = 1;
        }
        else if (checker.pipe)
        {
            if (input[i] == '|')
                return (258);
            if (!ft_isspace(input[i]))
                checker.pipe = 0;
        }
        else if (!checker.redirections && (input[i] == '>' || input[i] == '<'))
        {
            checker.redirections = 1;
            checker.redir_token = input[i];
            checker.redir_pos = i;
        }
        else if (checker.redirections)
        {
            if (input[checker.redir_pos + 1] && input[checker.redir_pos] == input[checker.redir_pos + 1] && \
            (input[i] == '|' || ((input[i] == '>' || input[i] == '<') && i != checker.redir_pos + 1)))
                return(258);

                
            if (!(checker.redir_token == input[i] && checker.redir_pos == i - 1) && \
            !(ft_isascii(input[i]) && !ft_isalnum(input[i])))
                checker.redirections = 0;
        }
        i++;
    }
    return check_vals(&checker);
}
