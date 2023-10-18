#include <libft.h>
#include <stdbool.h>

# define UNEXPECTED "minishell: syntax error near unexpected token "
# define QUOTES "minishell: syntax error, unclosed quote"
# define PIPES  "minishell: syntax error, unclosed pipe"

typedef struct s_input
{
    char    quote;
    char    redir_token;
    int     redir_pos;
    bool    pipe;
    bool    left_of_pipe;
    bool    redirections;
    int     return_val;
}   t_input;

void	check_quotes(t_input *checker, int i, char *input)
{
	if (!checker->quote && (input[i] == '\'' || input[i] == '"'))
		checker->quote = input[i];
	else if (checker->quote)
	{
		if (input[i] == checker->quote)
			checker->quote = 0;
	}
}

void	checker_redirections(t_input *checker, int i, char *input)
{
	if (i == checker->redir_pos + 1 && (input[i] == '|' || \
				(input[i] == '>' || input[i] == '<')))
	{
		if (checker->redir_token == '>' && input[i] == '<')
			checker->return_val = (258);
		else
			checker->return_val = -1;
	}
	else
	{
		if (input[i] == '>' || input[i] == '<')
			checker->return_val = ( 258);
	}
	if (input[i] != '|' && !ft_isspace(input[i]) && input[i] != checker->redir_token)
		checker->redirections = 0;
    else if (input[i] == '|')
        checker->return_val = 258;
	if ((input[i] == '>' || input[i] == '<') && input[i] != checker->redir_token)
		checker->return_val = (258);
}

void	check_pipes(t_input *checker, char *input, int i)
{
	if (!checker->pipe && input[i] == '|')
	{
		if (!checker->left_of_pipe)
			checker->return_val = ( 258);
		checker->pipe = 1;
	}
	else if (checker->pipe)
	{
		if (input[i] == '|')
			checker->return_val = (258);
		checker->pipe = 0;
	}
}
/*
int	(char *str, char *error, int code)
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
	return (print_error("\n", code));
}
*/
int	check_vals(t_input *checker)
{
	if (checker->quote)
		return ((1));
	if (checker->pipe)
		return (( 1));
	if (checker->redirections)
		return ((258));
	return (0);
}

void	init_checker(t_input *checker)
{
	checker->quote = 0;
	checker->left_of_pipe = 0;
	checker->pipe = 0;
	checker->redirections = 0;
	checker->redir_token = 0;
	checker->return_val = 0;
}

static void	set_vals_redirections(t_input *checker, char *input, int i)
{
	checker->redirections = 1;
	checker->redir_token = input[i];
	checker->redir_pos = i;
}

static void	parse_2(t_input *checker, char *input, int i)
{
	if (!checker->left_of_pipe && input[i] != '|')
		checker->left_of_pipe = 1;
	check_quotes(checker, i, input);
	check_pipes(checker, input, i);
}

int	parse_input(char *input)
{
	t_input	checker;
	int		i;

	init_checker(&checker);
	i = -1;
	while (input[++i])
	{
		if (ft_isspace(input[i]))
			continue ;
		if (!checker.redirections && !checker.quote && \
		(input[i] == '>' || input[i] == '<'))
			set_vals_redirections(&checker, input, i);
		else if (checker.redirections)
		{
			//printf("character [%s] checker.redirections {%i}\n", &input[i], checker.redirections);
			checker_redirections(&checker, i, input);
			//printf("checker.redirections {%i}\n", checker.redirections);

			if (checker.return_val == -1)
				continue ;
			else if (checker.return_val == 258)
				return (258);
		}
		parse_2(&checker, input, i);
		if (checker.return_val == 258)
			return (258);
	}
	return (check_vals(&checker));
}