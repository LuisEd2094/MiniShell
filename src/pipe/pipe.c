#include "MS_pipe.h"

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
	if (i < num_pipes - 1)
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

	pid = fork();
	if (pid == -1)
	{
		perror("Error en fork");
		return (1);
	}
	if (pid == 0)
	{
		duplicate_and_close(mini->pipes, num_pipes, i);
		if (check_and_handle_redirections(commands[i], mini))
		{	
			perror("Error en execute");
			return (1);
		}
	}
	return (0);
}

int	ft_pipe(char ***commands, int num_pipes, t_minishell *mini)
{
	int	i;

	mini->pipes = malloc_pipe(num_pipes);
	i = -1;
	if (make_pipe(mini->pipes, num_pipes))
		return (1);
	while (++i < num_pipes)
	{
		if (execute_pipe(commands, mini, num_pipes, i))
			return (1);
	}
	refinement(mini->pipes, num_pipes);
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
    int num_pipes = 1;

    while (commands[num_pipes])
        num_pipes++;
    printf("%d",ft_pipe(commands, num_pipes, mini));

    return 0;
}
*/
