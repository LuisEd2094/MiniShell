/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:06:05 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 13:09:29 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections_internal.h"
#include <fcntl.h>
#include <libft.h>

int	open_file(char *file_name, int redir_type)
{
	int	fd=0;

	if (redir_type == INPUT_REDIRECT)
	{
		if (access(file_name, R_OK) != 0)
			return (print_error(file_name, 1));
	}
	if (redir_type == INPUT_REDIRECT)
		fd = open(file_name, O_RDONLY);
	else if (redir_type == OUTPUT_REDIRECT)
		fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	else if (redir_type == APPEND_OUTPUT)
		fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (print_error(file_name, 1));
	return (fd);
}

int	execute_dup2(int fd, int redir_type)
{
	int	std_fd;

	if (redir_type == OUTPUT_REDIRECT || redir_type == APPEND_OUTPUT)
	{
		std_fd = dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else
	{
		std_fd = dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (std_fd < 0)
		return (0);
	return (1);
}

int	handle_redirection(char *redirection, char *file_name)
{
	int	redir_type;

	redir_type = get_redir_type(redirection);
	if (!execute_dup2(open_file(file_name, redir_type), redir_type))
		return (0);
	return (1);
}

void	remove_redir_from_cmds(char **cmds, int i)
{
	int		j;
	char	*temp;

	j = i + 2;
	while (cmds[j])
	{
		temp = cmds[i];
		cmds[i] = cmds[j];
		cmds[j] = temp;
		i++;
		j++;
	}
	while (i < j)
	{
		free(cmds[i]);
		cmds[i] = NULL;
		i++;
	}
}
