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

void	execute_pipe(char ***commands, t_minishell *mini, int num_pipes, int i)
{
	pid_t	pid;
	int		status;

	pid = fork();
	signal_action();
	if (pid == -1)
	{
		perror("Error en fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		setup_pipe(mini->pipes, num_pipes, i);
		if (check_and_handle_redirections(commands[i], mini))
		{
			perror("Error en execute");
			exit(EXIT_FAILURE);
		}
		execute_cmds(commands[i], mini->env_list));
		perror("Fallo execute_cmds");
		exit(127);
	}
}

int	ft_pipe(char ***commands, int num_pipes, t_minishell *mini)
{
	int	i;
	int	status;

	mini->pipes = malloc_pipe(num_pipes);
	if (mini->pipes == NULL)
		return (1);
	if (make_pipe(mini->pipes, num_pipes))
		return (1);
	i = -1;
	while (++i < num_pipes)
		execute_pipe(commands, mini, num_pipes, i);
	refinement(mini->pipes, num_pipes);
	i = -1;
	while (++i < num_pipes)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			return (WTERMSIG(status) + 128);
	}
	free_pipe(mini->pipes, num_pipes);
	return (0);
}

/*
#include <stdio.h>

int main() {
    char *command1[] = {"echo", "valor_de_hola", NULL};
    char *command2[] = {"cat", "main.c", NULL};
    char *command3[] = {"ls", "-la", NULL};
    char *command4[] = {"ls", "-la", NULL};

    char **commands[] = {command1, command2, command3, NULL};
    int num_commands = 0;

    while (commands[num_commands])
        num_commands++;
    printf("%d",ft_pipe(commands, num_commands - 1, mini));

    return 0;
}
*/
