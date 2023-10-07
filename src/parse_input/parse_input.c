

#include "parse_input_internal.h"


// need to check <> 
void init_checker(t_input *checker)
{
    checker->quote = 0;
    checker->left_of_pipe = 0;
    checker->pipe = 0;
    checker->redirections = 0;
    checker->redir_token = 0;
}

int     print_input_error(char *str, char *error, int code)
{
    print_error(str, code);
    if (error)
    {
        if (error[1])
        {
            if (error[0] == '|' && error[1] == '|')
                print_error("||", code);
            else if (error[0] == '|')
                print_error("|", code);
            else if (error[0] == '>' && error[1] == '>')
                print_error(">>", code);
            else if (error[0] == '>')
                print_error(">", code);
            else if (error[0] == '<')
            {
                if (error[2] && error[1] == '<' && error[2] == '<' )
                        print_error("<<<", code);
                else if (error[0] == '<' && error[1] == '<')
                    print_error("<<", code);
            }

        }
        else
            print_error(error, code);

    }
    print_error("\n", code);
    return (code);
}

int    check_vals(t_input *checker)
{
    if (checker->quote)
        return(print_input_error(QUOTES , NULL, 1));
    if (checker->pipe)
        return(print_input_error(PIPES, NULL, 1));
    if (checker->redirections)
        return(print_input_error(UNEXPECTED, "'newline'", 258));
    return (0);
}

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
                return(print_input_error(UNEXPECTED, &input[i], 258));
            if (i == checker.redir_pos + 1 && (input[i] == '|' || (input[i] == '>' || input[i] == '<')))
            {
                if (checker.redir_token == '>' && input[i] == '<')
                    return(print_input_error(UNEXPECTED, &input[i], 258));
                continue;
            }
            else
            {
                if (input[i] == '>' || input[i] == '<')
                    return(print_input_error(UNEXPECTED, &input[i], 258));
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
                return(print_input_error(UNEXPECTED, &input[i], 258));
            checker.pipe = 1;
        }
        else if (checker.pipe)
        {
            if (input[i] == '|')
                return(print_input_error(UNEXPECTED, &input[i], 258));
            checker.pipe = 0;
        }
    }
    return check_vals(&checker);
}