/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmacias- <gmacias-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 08:30:53 by gmacias-          #+#    #+#             */
/*   Updated: 2023/10/13 13:57:50 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipe.h>
#include <minishell.h>

void	setup_pipe(int **pipes, int num_pipes, int i)
{
	if (i > 0)
	{
		close(pipes[i - 1][1]);
		dup2(pipes[i - 1][0], STDIN_FILENO);
		close(pipes[i - 1][0]);
	}
	if (i < num_pipes)
	{
		close(pipes[i][0]);
		dup2(pipes[i][1], STDOUT_FILENO);
		close(pipes[i][1]);
	}
	refinement(pipes, num_pipes);
}

int	return_fork_error(int i, char *cmd)
{
	char *itoa;

	itoa = ft_itoa(i);
	print_error("Minishell: fork: Resource temporarily unavailable\
	\nMaking until command: ", 254);
	print_error(itoa, 254);
	free(itoa);
	print_error("\nCommand: ", 254);
	print_error(cmd, 254);
	return (print_error("\n", 254));
}

int	execute_pipe(char ***commands, t_minishell *mini, int num_pipes, int i)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		return (return_fork_error(i,commands[i][0]));
	}
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		status = check_quotes_and_env_and_redirections(mini->cmds[i], mini);
		if (status)
			exit(status);
		setup_pipe(mini->pipes, num_pipes, i);
		status = execute_cmds(commands[i], mini->env_list, mini);
		exit(status);
	}
	if (i == num_pipes)
		mini->last_pid = pid;
	return (0);
}

int	ft_pipe(char ***commands, int num_pipes, t_minishell *mini)
{
	int	i;
	int	status;
	int	last_status;

	last_status = 0;
	mini->pipes = malloc_pipe(num_pipes);
	if (mini->pipes == NULL)
		return (1);
	if (make_pipe(mini->pipes, num_pipes))
		return (1);
	i = -1;
	pipe_signal_action();
	while (++i <= num_pipes && last_status == 0 && g_received_signal == 0)
		last_status = execute_pipe(commands, mini, num_pipes, i);
	refinement(mini->pipes, num_pipes);
	status = 0;
	while (i-- != 0)
	{
		if (mini->last_pid == waitpid(-1, &status, 0) && last_status != 254)
			last_status = status;
	}
	free_pipe(mini->pipes, num_pipes);
	return (return_pipe(last_status));
}
