/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_start_and_argument_len.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:12:28 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 12:13:23 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_arguments_internal.h"

int	get_argument_len(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '\'' || cmd[i] == '"')
	{
		i = get_quotes_size(cmd);
		i -= 2;
	}
	else
		i = get_arg_size_skip_redirections(cmd);
	return (i);
}

int	move_start(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i] == '<' || cmd[i] == '>')
		return (get_redirection_size(&cmd[i]));
	else if (cmd[i] == '"' || cmd[i] == '\'')
		return (get_quotes_size(cmd));
	else
		return (get_argument_len(&cmd[i]));
}
