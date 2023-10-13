/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:35:26 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 10:37:30 by lsoto-do         ###   ########.fr       */
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
			{
				free(cmds[i][j]);
				cmds[i][j] = NULL;
			}
			j++;
		}
		free(cmds[i]);
		cmds[i] = NULL;
		i++;
	}
	free(cmds);
	cmds = NULL;
}

int	exit_mini(t_minishell *mini)
{
	work_history(CLOSE, NULL);
	free_env_list(mini->env_list);
	exit(0);
}

int close_redirections(t_minishell *mini)
{
    dup2(mini->og_in, STDIN_FILENO);
    dup2(mini->og_out, STDOUT_FILENO);
    return (0);
}
void	prep_mini(t_minishell *mini)
{
	char *exit_code;

	exit_code = ft_itoa(mini->exit_code);
	if (!exit_code)
		exit(EXIT_FAILURE);
	mini->here_doc_number = 0;
	free_cmds(mini->cmds);
	close_redirections(mini);
	signal_action();
	create_or_update_env_node(mini->env_list, "?", exit_code);
	free(exit_code);
	delete_temp_files(mini);
	received_signal = 0;
	if (errno)
		errno = 0;
}

void	init_mini(t_minishell *mini, char **env)
{
	char *exit_code;

	exit_code = ft_itoa(0);
	if (!exit_code)
		exit(EXIT_FAILURE);
	signal_action();
	mini->exit_code = 0;
	mini->input_code = 0;
	mini->env_list = init_env(env);
	create_or_update_env_node(mini->env_list, "?" , exit_code);
	free(exit_code);
    mini->og_in = dup(STDIN_FILENO);
    mini->og_out = dup(STDOUT_FILENO);
	if (!mini->env_list)
		exit(EXIT_FAILURE);
	work_history(INIT, NULL);
	mini->here_doc_number = 0;
}
