/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:46:01 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 11:47:25 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	compare_cmds(char *cmd, char *to_compare)
{
	if (ft_strcmp(cmd, to_compare) \
		== 0)
		return (1);
	return (0);
}

bool	is_built_in(char **cmds)
{
	if (!cmds[0])
		return (0);
	if (compare_cmds(cmds[0], "env"))
		return (1);
	else if (compare_cmds(cmds[0], "export"))
		return (1);
	else if (compare_cmds(cmds[0], "unset"))
		return (1);
	else if (compare_cmds(cmds[0], "pwd"))
		return (1);
	else if (compare_cmds(cmds[0], "echo"))
		return (1);
	else if (compare_cmds(cmds[0], "cd"))
		return (1);
	else if (compare_cmds(cmds[0], "exit"))
		return (1);
	return (0);
}

int	execute_cmds(char **cmds, t_list *env_list, t_minishell *mini)
{
	if (!cmds[0])
		return (0);
	if (compare_cmds(cmds[0], "env"))
		return (ft_print_env(cmds, env_list));
	else if (compare_cmds(cmds[0], "export"))
		return (ft_export(env_list, cmds));
	else if (compare_cmds(cmds[0], "unset"))
		return (ft_unset(cmds, mini));
	else if (compare_cmds(cmds[0], "pwd"))
		return (ft_pwd(cmds));
	else if (compare_cmds(cmds[0], "echo"))
		return (ft_echo(cmds));
	else if (compare_cmds(cmds[0], "cd"))
		return (ft_cd(cmds, env_list));
	else if (compare_cmds(cmds[0], "exit"))
		return (ft_exit(cmds, mini));
	else
		return(try_execve(cmds, env_list));
}

int	handle_single_builtin(t_minishell *mini)
{
	check_quotes_and_env(mini->cmds[0], mini);
	return (execute_cmds(mini->cmds[0], mini->env_list, mini));
}

void	start_execute_cmds(t_minishell *mini)
{
	int	num_commands;

	num_commands = 0;
	while (mini->cmds[num_commands])
		num_commands++;
	if (num_commands > 1)
		mini->exit_code = ft_pipe(mini->cmds, num_commands - 1, mini);
	else if (num_commands == 1)
	{
		if (is_built_in(mini->cmds[0]))
			mini->exit_code = handle_single_builtin(mini);
		else
			mini->exit_code = ft_pipe(mini->cmds, num_commands -1, mini);
	}
}
