/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:37:14 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 14:34:29 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_input_internal.h"

static void	init_checker(t_input *checker)
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
	if (i == checker->redir_pos + 1 && ((input[i] == '>' || input[i] == '<')))
	{
		if (input[i] != checker->redir_token)
			checker->return_val = print_input_error(UNEXPECTED, &input[i], 258);
	}
	else
	{
		if (input[i] == '>' || input[i] == '<' || input[i] == '|')
			checker->return_val = print_input_error(UNEXPECTED, &input[i], 258);
		else if (!ft_isspace(input[i]))
		{
			checker->redirections = 0;
			checker->return_val = 0;
		}
	}
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
		if (checker.redirections && !checker.quote)
			checker_redirections(&checker, i, input);
		if (checker.quote || (input[i] == '\'' || input[i] == '"'))
			check_quotes(&checker, i, input);
		else if (!checker.redirections && \
		(input[i] == '>' || input[i] == '<'))
			set_vals_redirections(&checker, input, i);
		if (!checker.quote)
			check_pipes(&checker, input, i); 
		if (checker.return_val == 258)
			return (checker.return_val);
	}
	return (check_vals(&checker));
}
