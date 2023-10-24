/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:23:44 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/18 10:07:22 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_cmds(char ***cmds)
{
	int	i;
	int	j;

	i = 0;
	while (cmds[i])
	{
		j = 0;
		while (cmds[i][j])
		{
			if (cmds[i][j])
				free(cmds[i][j]);
			j++;
		}
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

int	exit_mini(t_minishell *mini)
{
	reset_terminal(mini);
	work_history(CLOSE, NULL);
	free_env_list(mini->env_list);
	if (mini->cmds)
	{
		free_cmds(mini->cmds);
		mini->cmds = NULL;
	}
	if (mini->input)
		free(mini->input);
	exit(mini->exit_code);
}

void	update_exit_value(t_minishell *mini)
{
	char *code;
	
	if (g_received_signal)
		code = ft_itoa(1);
	else
		code = ft_itoa(mini->exit_code);
	if (!code)
		exit_mini(mini);
	create_or_update_env_node(mini->env_list, "?", code);
	free(code);
}

void	prep_mini(t_minishell *mini)
{
	update_exit_value(mini);
	if (mini->cmds)
	{
		free_cmds(mini->cmds);
		mini->cmds = NULL;
	}
	close_redirections(mini);
	signal_action();
	mini->code_here_doc = 0;
	mini->here_quotes = 0;
	mini->exit_code = 0;
	mini->input_code = 0;
	g_received_signal = 0;
	delete_temp_files(mini);
	if (errno)
		errno = 0;
}

void	init_mini(t_minishell *mini, char **env)
{
	prep_terminal(mini);
	signal_action();
	mini->code_here_doc = 0;
	mini->here_quotes = 0;
	mini->exit_code = 0;
	mini->input_code = 0;
	mini->env_list = init_env(env);
	create_or_update_env_node(mini->env_list, "?", "0");
	remove_node("OLDPWD", mini);
	if (!check_shlvl(mini->env_list))
		exit(EXIT_FAILURE);
	mini->og_in = dup(STDIN_FILENO);
	mini->og_out = dup(STDOUT_FILENO);
	if (!mini->env_list)
		exit(EXIT_FAILURE);
	work_history(INIT, NULL);
	mini->here_doc_number = 0;
	mini->cmds = NULL;
}
