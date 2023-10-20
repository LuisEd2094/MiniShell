/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_argument_aux.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:04:00 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/18 13:02:40 by gmacias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_arguments_internal.h"

int	get_argument_count(char *cmd)
{
	int	i;
	int	arg_count;

	i = 0;
	arg_count = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\"' || cmd[i] == '\'' || \
			cmd[i] == '>' || cmd[i] == '<' || \
			is_ascii_no_space(cmd[i]))
		{
			if ((i == 0 && (cmd[i] == '\"' || cmd[i] == '\'')) || \
				((cmd[i] == '\"' || cmd[i] == '\'') && \
				cmd[i - 1] == ' '))
				i += get_quotes_size(&cmd[i]);
			else if (cmd[i] == '>' || cmd[i] == '<')
				i += get_redirection_size(&cmd[i]);
			else if (is_ascii_no_space(cmd[i]))
				i += get_arg_size_skip_redirections(&cmd[i]);
			arg_count++;
		}
		else
			i++;
	}
	return (arg_count);
}

int	get_cmd_count(char **cmds)
{
	int	cmd_count;

	cmd_count = 0;
	while (cmds[cmd_count])
		cmd_count++;
	return (cmd_count);
}

int	ft_commands_count(char *input)
{
	int	i;
	int	count;

	i = -1;
	count = 1;
	while (input[++i])
	{
		if (input[i] == '"' || input[i] == '\'')
			i += get_quotes_size(&input[i]) - 1;
		else if (input[i] == '|')
			count++;
	}
	return (count);
}
