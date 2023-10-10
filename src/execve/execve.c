/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:48:24 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 11:53:40 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <execve.h>
#include <builtins.h>
#include "execve_internal.h"
#include <shared.h>


char	**conver_env_list(t_list *env_list)
{
	int		i;
	t_list	*temp;
	char	**new;

	temp = env_list;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	new = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (print_perror());
	i = 0;
	temp = env_list;
	while (temp)
	{
		new[i] = reconstruct_env(((t_env *)(temp->content))->variable, \
				((t_env *)(temp->content))->value);
		if (!new[i])
		{
			print_perror();
			return(free_2d_array(new));
		}
		temp = temp->next;
		i++;
	}
	new[i] = NULL;
	return (new);
}

char	**get_paths(t_list *path_node)
{
	char	**tab;

	if (!path_node)
		return (NULL);
	tab = ft_split(((t_env *)(path_node->content))->value, ':');
	if (!tab)
		return (NULL);
	return (tab);
}

char	*get_path_name(char **cmd, char **path_list)
{
	char	*path_name;
	int		i;

	if (!path_list)
	{
		if (errno != ENOMEM)
			errno = ENOENT;
		return (NULL);
	}
	path_name = NULL;
	i = 0;
	while (path_list[i])
	{
		if (path_list[i][ft_strlen(path_list[i])] != '/')
			path_name = join_path(path_list[i], cmd[0]);
		else
			path_name = ft_strjoin(path_list[i], cmd[0]);
		if (!path_name)
		{
			free_2d_array(path_list);
			return (print_perror());
		}
		if (access(path_name, F_OK) != -1 && access(path_name, X_OK) != -1)
			break ;
		free(path_name);
		path_name = NULL;
		i++;
	}
	errno = 0;
	free_2d_array(path_list);
	return (path_name);
}

int	try_execve(char **cmd, t_list *env_list)
{
	char	**converted_env_list;
	char	*path_name;

	if (access(cmd[0], F_OK) != -1 && access(cmd[0], X_OK) != -1)
		path_name = cmd[0];
	else
		path_name = get_path_name(cmd, get_paths(get_env_node(env_list, "PATH")));
	if (path_name)
	{
		converted_env_list = conver_env_list(env_list);
		if (!converted_env_list)
		{
			free(path_name);
			return (errno);
		}
		execve(path_name, cmd, converted_env_list);
		perror("minishell :");
		exit(EXIT_FAILURE);
	}
	else
	{
		if (errno == ENOMEM)
			print_perror();
		else
		{
			write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
			write(STDERR_FILENO, cmd[0], ft_strlen(cmd[0]));
			write(STDERR_FILENO, ": ", ft_strlen(": "));
			if (errno == ENOENT)
				perror(NULL);
			else
				write(STDERR_FILENO, "command not found\n", ft_strlen( ": command not found\n"));
		}
		return (127);
	}
}
