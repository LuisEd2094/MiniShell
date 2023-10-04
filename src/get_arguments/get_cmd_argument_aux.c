/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_argument_aux.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:10:41 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 12:14:12 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	get_argument_count(char *cmd)
{
	int	i;
	int	arg_count;

	i = 0;
	arg_count = 0;
	while (cmd[i])
	{
		if (cmd [i] == '\"' || cmd[i] == '\'' || \
			cmd[i] == '>' || cmd[i] == '<' || \
			is_ascii_no_space(cmd[i]))
		{
			if (cmd [i] == '\"' || cmd[i] == '\'')
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