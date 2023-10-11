/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:22:44 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 10:35:08 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdlib.h>
#include <unistd.h>

void	main_loop(t_minishell *mini)
{
	while (1)
	{
		mini->input = readline(">> ");
		if (!mini->input)
			exit_mini(mini);
		if (ft_strncmp(mini->input, "exit", ft_strlen("exit") + 1) == 0)
		{
			free(mini->input);
			break ;
		}
		if (mini->input[0] != '\0')
		{
			work_history(UPDATE, mini->input);
			mini->input_code = parse_input(mini->input);
			if	(mini->input_code == 0)
			{
				mini->cmds = get_cmds_value(mini->input);
				create_here_doc(mini);

				printf("Before [%i]exit code\n", mini->exit_code);
				start_execute_cmds(mini);
				printf("After [%i]exit code\n", mini->exit_code);
				prep_mini(mini);
				printf("After [%i]exit code\n", mini->exit_code);

			}
			else
				mini->exit_code = mini->input_code;
		}

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
	free_env_list(mini.env_list);
	work_history(CLOSE, NULL);
	return (0);
}
