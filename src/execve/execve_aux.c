/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:56:04 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 11:56:32 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve_internal.h"

char	*join_path(char *path_list, char *cmd)
{
	char	*temp_path;
	char	*path_name;

	temp_path = ft_strjoin(path_list, "/");
	if (!temp_path)
		return (NULL);
	path_name = ft_strjoin(temp_path, cmd);
	free(temp_path);
	return (path_name);
}

char	*reconstruct_env(char	*variable, char	*value)
{
	char	*new;
	char	*temp;

	temp = ft_strjoin(variable, "=");
	if (!temp)
		return (NULL);
	new = ft_strjoin(temp, value);
	free(temp);
	if (!new)
		return (NULL);
	return (new);
}

int get_env_list_size(t_list *env_list)
{
	int	i;
	t_list	*temp;

	temp = env_list;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

void	*no_list(void)
{
	if (errno != ENOMEM)
		errno = ENOENT;
	return (NULL);
}

int	no_path_name_found(char *cmd)
{
	if (errno == ENOMEM)
	{
		print_perror();
		return (errno);
	}
	else
	{
		write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": ", ft_strlen(": "));
		if (errno == ENOENT)
			perror(NULL);
		else
			write(STDERR_FILENO, "command not found\n", ft_strlen("command not found\n"));
		return (127);
	}
	
}