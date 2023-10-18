/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes_and_env_and_redirections.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:25:49 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/18 10:26:06 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute_cmds_internal.h"

int	remove_quote(char *str, int i, char quote)
{
	int	j;
	int	size;

	j = i + 1;
	size = 0;
	while (str[j] != quote)
	{
		str[i] = str[j];
		i++;
		j++;
		size++;
	}
	j += 1;
	while (str[j])
	{
		str[i] = str[j];
		i++;
		j++;
	}
	str[j - 1] = '\0';
	str[j - 2] = '\0';
	size--;
	return (size);
}

char	*replace_exit_code(t_minishell *mini, char *cmd)
{
	char	*exit_code;
	char	*temp;

	exit_code = get_env_str_from_quote("?", mini->env_list);
	temp = cmd;
	cmd = ft_replace(cmd, exit_code, 0, 0);
	free(temp);
	free(exit_code);
	return (cmd);
}

char	*replace_values(char *cmd, t_minishell *mini)
{
	int i;
	char	*env;

	i = -1;
	while (cmd[++i])
	{
		if (cmd[i] == '"' || cmd[i] == '\'' || (cmd[i] == '$' && cmd[i + 1] && is_ascii_no_space(cmd[i + 1])))
		{
			if (cmd[i] == '"')
			{
				cmd = get_double_quote(cmd, mini->env_list, i);
				printf("After get double quotes [%s]\n", cmd);
				i += remove_quote(cmd, i, '"');
			}
			else if (cmd[i] == '\'')
				i += remove_quote(cmd, i, '\'');		
			else if (cmd[i] == '$' && \
			cmd[i + 1] && \
			is_ascii_no_space(cmd[i + 1]))
			{
				if (cmd[i + 1] == '?')
					env = get_env_str(ft_substr(cmd, i + 1, 1), mini->env_list);
				else
					env = get_env_str_from_quote(&cmd[i + 1], mini->env_list);
				cmd = replace_env(cmd, env, i);
				i += ft_strlen(env) - 1;
				free(env);
			}
			if (!cmd)
				return (NULL);
		}
	}
	return (cmd);
}

int	ft_redirections(char **cmd, t_minishell *mini, int i)
{
	char	*og_command;

	og_command = "";
	og_command = ft_strjoin(og_command, cmd[i + 1]);
	cmd[i + 1] = replace_values(cmd[i + 1], mini);
	if (!cmd[i + 1][0])
	{
		print_error("minishell: ", 1);
		print_error(og_command, 1);
		free(og_command);
		return (print_error(": ambiguous redirect\n", 1));
	}
	check_and_handle_redirections(cmd[i], cmd[i + 1], mini);
	free(og_command);
	remove_cmds_from_cmds(cmd, i, 2);
	return (0);
}

int	check_quotes_and_env_and_redirections(char **cmd, t_minishell *mini)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '>' || cmd[i][0] == '<')
		{
			status = ft_redirections(cmd, mini, i);
			if (status)
				return (status);
			i--;
		}

		else
			cmd[i] = replace_values(cmd[i], mini);
		i++;
	}
	return (status);
}
