#include <minishell.h>

bool	compare_cmds(char *cmd, char *to_compare)
{
	if (ft_strncmp(cmd, to_compare, ft_strlen(to_compare)) \
		== 0)
		return (1);
	return (0);
}

bool	is_built_in(char **cmds)
{
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
	return (0);
}

int	execute_cmds(char **cmds, t_list *env_list)
{
	if (compare_cmds(cmds[0], "env"))
		ft_env(env_list);
	else if (compare_cmds(cmds[0], "export"))
		return (ft_export(env_list, cmds));
	else if (compare_cmds(cmds[0], "unset"))
		ft_unset(env_list, cmds[1]);
	else if (compare_cmds(cmds[0], "pwd"))
		return (ft_pwd(cmds));
	else if (compare_cmds(cmds[0], "echo"))
		return (ft_echo(cmds));
	else if (compare_cmds(cmds[0], "cd"))
		return (ft_cd(cmds, env_list));
	else
		try_execve(cmds, env_list);
	return (0);
}

int	handle_single_built_int(t_minishell *mini)
{
	check_and_handle_redirections(mini->cmds[0], mini);
	return (execute_cmds(mini->cmds[0], mini->env_list));
}

void	start_execute_cmds(t_minishell *mini)
{
	int	num_pipes;

	num_pipes = 0;
	while (mini->cmds[num_pipes])
		num_pipes++;
	if (num_pipes > 1)
		mini->exit_code = ft_pipe(mini->cmds, num_pipes, mini);
	else if (num_pipes == 1)
	{
		if (is_built_in(mini->cmds[0]))
			mini->exit_code = handle_single_built_int(mini);
		else
			mini->exit_code = ft_pipe(mini->cmds, num_pipes, mini);
	}
}
