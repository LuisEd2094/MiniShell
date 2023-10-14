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

void	init_checker(t_input *checker)
{
	checker->quote = 0;
	checker->left_of_pipe = 0;
	checker->pipe = 0;
	checker->redirections = 0;
	checker->redir_token = 0;
	checker->return_val = 0;
}

static void	check_redirections(t_input *checker, char *input, int i)
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
		if (input[i] == ';')
			return (1);
		if (!checker.redirections && !checker.quote && \
		(input[i] == '>' || input[i] == '<'))
			check_redirections(&checker, input, i);
		else if (checker.redirections)
		{
			checker_redirections(&checker, i, input);
			if (checker.return_val == -1)
				continue ;
			else if (checker.return_val == 258)
				return (checker.return_val);
		}
		parse_2(&checker, input, i);
		if (checker.return_val == 258)
			return (checker.return_val);
	}
	return (check_vals(&checker));
}
