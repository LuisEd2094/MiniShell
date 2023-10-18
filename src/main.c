/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:22:44 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 13:23:09 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>
#include <unistd.h>

void	execute_loop(t_minishell *mini)
{
	work_history(UPDATE, mini->input);
	mini->input_code = parse_input(mini->input);
	if (mini->input_code == 0)
	{
		mini->cmds = get_cmds_value(mini->input);
		for (int i = 0; mini->cmds[i];i++)
		{
			for (int j = 0; mini->cmds[i][j]; j++)
				ft_printf("[%s]\n", mini->cmds[i][j]);
		}
		mini->code_here_doc = create_here_doc(mini);
		if (mini->code_here_doc == 0)
			start_execute_cmds(mini);
		else
			mini->exit_code = mini->code_here_doc;
	}
	else
		mini->exit_code = mini->input_code;
}

void	main_loop(t_minishell *mini)
{
	while (1)
	{
		mini->input = readline(">> ");
		if (!mini->input)
		{
			if (isatty(STDIN_FILENO))
				write(2, "exit\n", 6);
			exit_mini(mini);
		}
		if (mini->input[0] != '\0')
			execute_loop(mini);
		prep_mini(mini);
		free(mini->input);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	mini;

	if (argc > 1 || argv[1])
		exit(1);
	init_mini(&mini, env);
	main_loop(&mini);
	exit_mini(&mini);
}
