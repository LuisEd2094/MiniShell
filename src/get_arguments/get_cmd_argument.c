/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_argument.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:57:30 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 13:03:37 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_arguments_internal.h"

char	*ft_get_arg(char *cmd, int arg_start)
{
	int	arg_len;

	arg_len = 0;
	if (cmd[arg_start])
	{
		if ((arg_start == 0 && (cmd[arg_start] == '\"' || \
		cmd[arg_start] == '\'')) || ((cmd[arg_start] == '\"' || \
		cmd[arg_start] == '\'') && cmd[arg_start - 1] == ' '))
			arg_len += get_quotes_size(&cmd[arg_start]);
		else if (cmd[arg_start] == '>' || cmd[arg_start] == '<')
			arg_len += get_redirection_size(&cmd[arg_start]);
		else if (is_ascii_no_space(cmd[arg_start]))
			arg_len += get_arg_size_skip_redirections(&cmd[arg_start]);
	}
	else
		return (NULL);
	return (ft_substr(cmd, arg_start, arg_len));
}

char	**ft_argument_split(char *cmd)
{
	char	**args;
	int		arg_count;
	int		i;
	int		arg_start;

	arg_count = get_argument_count(cmd);
	args = (char **)malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		exit (1);
	i = 0;
	arg_start = 0;
	while (i < arg_count)
	{
		arg_start += get_white_space_size(&cmd[arg_start]);
		args[i] = ft_get_arg(cmd, arg_start);
		if (!args[i])
			exit (1);
		arg_start += ft_strlen(args[i]);
		i++;
	}
	args[i] = NULL;
	return (args);
}

char	**get_cmd_argument(char *cmd)
{
	char	**cmd_arguments;

	if (!cmd)
		return (NULL);
	cmd_arguments = ft_argument_split(cmd);
	if (!cmd_arguments)
		return (NULL);
	return (cmd_arguments);
}
