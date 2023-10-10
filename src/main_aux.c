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
				free(cmds[i][j]);
			j++;
		}
		free(cmds[i]);
		i++;
	}
	free(cmds);
}

void	exit_mini(t_minishell *mini)
{
	work_history(CLOSE, NULL);
	free_env_list(mini->env_list);
	exit(0);
}

void	prep_mini(t_minishell *mini)
{
	mini->here_doc_number = 0;
	free_cmds(mini->cmds);
	delete_temp_files(mini);
	if (errno)
		errno = 0;
}

void	init_mini(t_minishell *mini, char **env)
{
	mini->exit_code = 0;
	mini->env_list = init_env(env);
	mini->here_doc_number = 0;
	mini->og_in = dup(STDIN_FILENO);
	mini->og_out = dup(STDOUT_FILENO);
	work_history(INIT, NULL);
	signal_action();
}
