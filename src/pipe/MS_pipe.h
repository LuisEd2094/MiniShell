#ifndef MS_FUNCTIONS_H
# define MS_FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/*	---	Memory pipe	---	*/
int	**malloc_pipe(int num_pipes);
void	free_pipe(int **pipes, int num_pipes);

/*  ---  Pipe  ---  */
int	ft_pipe(char ***commands, int num_pipes)

#endif
