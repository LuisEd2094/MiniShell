#include "MS_pipe.h"

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
			perror("Error en malloc");
			return (NULL);
		}
	}
	return (pipes);
}

void	free_pipe(int **pipes, int num_pipes)
{
	int	i;

	i = -1;
	while (++i < num_pipes)
		free(pipes[i]);
	free(pipes);
}
