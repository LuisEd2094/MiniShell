/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmacias- <gmacias-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 08:30:42 by gmacias-          #+#    #+#             */
/*   Updated: 2023/10/13 14:37:03 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <minishell.h>

/*	---	Memory pipe	---	*/
int		**malloc_pipe(int num_pipes);
void	free_pipe(int **pipes, int num_pipes);
int		return_pipe(int last_status);
int     make_pipe(int **pipes, int num_pipes);
void	refinement(int **pipes, int num_pipes);


/*  ---  Pipe  ---  */
int		ft_pipe(char ***commands, int num_pipes, t_minishell *mini);
int		get_exit_code(int status);


#endif
