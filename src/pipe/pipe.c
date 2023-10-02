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
** Redirige entrada desde la tubería anterior (excepto para el primer comando)
** Redirige salida a la tubería actual (excepto para el último comando)
** Cierra todas las otras tuberías en este proceso hijo
*/

void	duplicate_and_close(int **pipes, int num_pipes, int i)
{
	int	j;

	if (i > 0)
	{
		dup2(pipes[i - 1][0], STDIN_FILENO);
		close(pipes[i - 1][0]);
	}
	if (i < num_pipes -1)
	{
		dup2(pipes[i][1], STDOUT_FILENO);
		close(pipes[i][1]);
	}
	j = -1;
	while (++j < num_pipes - 1)
	{
		if (j != i)
		{
			close(pipes[j][0]);
			close(pipes[j][1]);
		}
	}
}

/*
** Cierra todas las tuberías en el proceso padre
** Espera a que todos los procesos hijos terminen
*/

void	refinement(int **pipes, int num_pipes)
{
	int	i;

	i = -1;
	while (++i < num_pipes - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
	}
	i = -1;
	while (++i < num_pipes)
		wait(NULL);
}

int	execute_pipe(char ***commands, t_minishell *mini, int num_pipes, int i)
{
	pid_t	pid;
	int		status;

		status = 0;
	if (status)
		status = 0;


	printf("I am about to fork, the i cmd is [%s] \n", commands[i][0]);
	pid = fork();
	signal_action();
	if (pid == -1)
	{
		perror("Error en fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
		duplicate_and_close(mini->pipes, num_pipes, i);
		if (check_and_handle_redirections(commands[i], mini))
		{
			perror("Error en execute");
			exit(EXIT_FAILURE);
		}
		exit(execute_cmds(commands[i], mini->env_list));
	}
	else
	{
		printf("i am about to wait my cmd is [%s\n", commands[i][0]);
		wait(NULL);
		printf("just woke up my command was [%s] \n", commands[i][0]);
		return (0);
		//return (get_exit_code(status));
	}

	return (0);
}

int	ft_pipe(char ***commands, int num_pipes, t_minishell *mini)
{
	int	i;
	int	exit_code;

	mini->pipes = malloc_pipe(num_pipes);
	if (mini->pipes == NULL)
		return (1);
	i = -1;
	//printf("[%i] Pipe nums\n", num_pipes);
	if (make_pipe(mini->pipes, num_pipes))
		return (1);
	while (commands[++i])
	{
		//printf("command before execute [%s]\n", commands[i][0]);
		exit_code = execute_pipe(commands, mini, num_pipes, i);
		printf("i just left my execute, my command was [%s]\n", commands[i][0]);
		if (exit_code)
		{
			free_pipe(mini->pipes, num_pipes);
			return (exit_code);
		}
	}
	refinement(mini->pipes, num_pipes);
	free_pipe(mini->pipes, num_pipes);
	return (exit_code);
}

/*
#include <stdio.h>

int main() {
    char *command1[] = {"echo", "valor_de_hola", NULL};
    char *command2[] = {"cat", "main.c", NULL};
    char *command3[] = {"ls", "-la", NULL};
    char *command4[] = {"ls", "-la", NULL};

    char **commands[] = {command1, command2, command3, NULL};
    int num_pipes = 1;

    while (commands[num_pipes])
        num_pipes++;
    printf("%d",ft_pipe(commands, num_pipes, mini));

    return 0;
}
*/
