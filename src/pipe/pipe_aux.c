/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_aux.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:54:57 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 13:56:31 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pipe.h>
#include <minishell.h>

int	return_pipe(int last_status)
{
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	else if (WIFSIGNALED(last_status))
		return (WTERMSIG(last_status) + 128);
	return (0);
}
