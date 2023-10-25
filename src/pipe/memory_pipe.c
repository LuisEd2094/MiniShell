/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmacias- <gmacias-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 08:31:46 by gmacias-          #+#    #+#             */
/*   Updated: 2023/10/02 08:44:48 by gmacias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipe.h>

int	return_pipe(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (status);
}

void	free_pipe(int **pipes, int num_pipes)
{
	int	i;

	i = -1;
	while (++i < num_pipes)
		free(pipes[i]);
	free(pipes);
	pipes = NULL;
}

int	**malloc_pipe(int num_pipes)
{
	int	i;
	int	**pipes;

	pipes = (int **)malloc((num_pipes + 1) * sizeof(int *));
	if (pipes == NULL)
	{
		perror("minishell: pipe: malloc() failed:");
		return (NULL);
	}
	i = -1;
	while (++i < num_pipes)
	{
		pipes[i] = (int *)malloc(2 * sizeof(int));
		if (pipes[i] == NULL)
		{
			free_pipe(pipes, i);
			perror("minishell: pipe: malloc() failed:");
			return (NULL);
		}
	}
	pipes[i] = NULL;
	return (pipes);
}

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

int	make_pipe(int **pipes, int num_pipes)
{
	int	i;

	i = -1;
	while (++i < num_pipes)
	{
		if (pipe(pipes[i]) == -1)
		{
			refinement(pipes, i - 1);
			free_pipe(pipes, num_pipes);
			perror("minishell: pipe: Error with pipes");
			return (1);
		}
	}
	return (0);
}
