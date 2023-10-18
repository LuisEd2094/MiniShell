/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_aux.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 14:32:20 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/18 13:04:36 by gmacias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_input_internal.h"

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
			checker->return_val = (258);
	}
	if (input[i] != '|' && !ft_isspace(input[i]) && \
			input[i] != checker->redir_token)
		checker->redirections = 0;
	else if (input[i] == '|')
		checker->return_val = 258;
	if ((input[i] == '>' || input[i] == '<') && \
			input[i] != checker->redir_token)
		checker->return_val = (258);
}

void	check_pipes(t_input *checker, char *input, int i)
{
	if (!checker->pipe && input[i] == '|')
	{
		if (!checker->left_of_pipe)
			checker->return_val = print_input_error(UNEXPECTED, &input[i], 258);
		checker->pipe = 1;
	}
	else if (checker->pipe)
	{
		if (input[i] == '|')
			checker->return_val = print_input_error(UNEXPECTED, &input[i], 258);
		checker->pipe = 0;
	}
}

int	print_input_error(char *str, char *error, int code)
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

int	check_vals(t_input *checker)
{
	if (checker->quote)
		return (print_input_error(QUOTES, NULL, 1));
	if (checker->pipe)
		return (print_input_error(PIPES, NULL, 1));
	if (checker->redirections)
		return (print_input_error(UNEXPECTED, "'newline'", 258));
	return (0);
}
