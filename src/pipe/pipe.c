/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmacias- <gmacias-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 08:30:53 by gmacias-          #+#    #+#             */
/*   Updated: 2023/10/02 08:44:43 by gmacias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipe.h>

int	make_pipe(int **pipes, int num_pipes)
{
	int	i;

	i = -1;
	while (++i < num_pipes)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("Error en pipe");
			return (1);
		}
	}
	return (0);
}

/*
** Cierra todas las tuberías en el proceso padre
** Espera a que todos los procesos hijos terminen
*/

void	refinement(int **pipes, int num_pipes)
{
	int	i;

	i = -1;
	while (++i < num_pipes)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
}

/*
** Redirige entrada desde la tubería anterior (excepto para el primer comando)
** Redirige salida a la tubería actual (excepto para el último comando)
** Cierra todas las otras tuberías en este proceso hijo
*/

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

int	execute_pipe(char ***commands, t_minishell *mini, int num_pipes, int i)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
	{
		perror("Error en fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		//signal_action();
		setup_pipe(mini->pipes, num_pipes, i);
		check_quotes_and_env(mini->cmds[i], mini);
/*

		if (check_and_handle_redirections(commands[i], mini))
		{
			perror("Error en execute");
			exit(EXIT_FAILURE);
		}*/
		status = execute_cmds(commands[i], mini->env_list, mini);

		free_env_list(mini->env_list);
		free_cmds(mini->cmds);
		free(mini->input);
		refinement(mini->pipes, num_pipes);
		free_pipe(mini->pipes, num_pipes);
		work_history(CLOSE, NULL);
		exit(status);
	}
	if (i == num_pipes)
	{
		mini->last_pid  = pid;
	}
	return (0);
}

int	ft_pipe(char ***commands, int num_pipes, t_minishell *mini)
{
	int	i;
	int	status;
	int last_status;


	mini->pipes = malloc_pipe(num_pipes);
	if (mini->pipes == NULL)
		return (1);
	if (make_pipe(mini->pipes, num_pipes))
		return (1);
	i = -1;

	while (++i <= num_pipes)
		execute_pipe(commands, mini, num_pipes, i);
	refinement(mini->pipes, num_pipes);
	i = -1;
	while (++i <= num_pipes)
	{
		status = 0;
		if (mini->last_pid == waitpid(-1, &status, 0))
			last_status = status;	
	}
	free_pipe(mini->pipes, num_pipes);
	if (WIFEXITED(last_status))
	{
		return (WEXITSTATUS(last_status));
	}
	else if (WIFSIGNALED(last_status))
		return (WTERMSIG(last_status) + 128);
	return (0);
}