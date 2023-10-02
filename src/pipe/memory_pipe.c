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

void	wait_pipe(int status)
{
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
}

void	free_pipe(int **pipes, int num_pipes)
{
	int	i;

	i = -1;
	while (++i < num_pipes)
		free(pipes[i]);
	free(pipes);
}

int	**malloc_pipe(int num_pipes)
{
	int	i;
	int	**pipes;

	pipes = (int **)malloc((num_pipes) * sizeof(int *));
	if (pipes == NULL)
	{
		perror("Error en malloc");
		return (NULL);
	}
	i = -1;
	while (++i < num_pipes)
	{
		pipes[i] = (int *)malloc(2 * sizeof(int));
		if (pipes[i] == NULL)
		{
			free_pipe(pipes, i);
			perror("Error en malloc");
			return (NULL);
		}
	}
	return (pipes);
}
