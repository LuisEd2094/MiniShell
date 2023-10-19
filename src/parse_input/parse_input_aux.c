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


void	check_pipes(t_input *checker, char *input, int i)
{
	if (!checker->left_of_pipe && input[i] != '|')
		checker->left_of_pipe = 1;
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

static void print_input_helper(char *error, int code)
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

int	print_input_error(char *str, char *error, int code)
{
	print_error(str, code);
	if (error)
	{
		if (error[1])
			print_input_helper(error, code);
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
