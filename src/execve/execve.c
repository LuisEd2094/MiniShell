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
		temp = temp->next;
		i++;
	}
	new[i] = NULL;
	return (new);
}

char	**get_paths(t_list *path_node)
{
	char	**tab;

	tab = ft_split(((t_env *)(path_node->content))->value, ':');
	if (!tab)
		exit (1);
	return (tab);
}

char	*get_path_name(char **cmd, char **path_list)
{
	char	*path_name;
	int		i;

	path_name = NULL;
	i = 0;
	while (path_list[i])
	{
		if (path_list[i][ft_strlen(path_list[i])] != '/')
			path_name = join_path(path_list[i], cmd[0]);
		else
			path_name = ft_strjoin(path_list[i], cmd[0]);
		if (!path_name)
			exit (1);
		if (access(path_name, F_OK) != -1 && access(path_name, X_OK) != -1)
			break ;
		free(path_name);
		path_name = NULL;
		i++;
	}
	free_path_list(path_list);
	
	return (path_name);
}

int	try_execve(char **cmd, t_list *env_list)
{
	char	**converted_env_list;
	char	*path_name;

	path_name = get_path_name(cmd, get_paths(get_env_node(env_list, "PATH")));
	if (path_name)
	{
		converted_env_list = conver_env_list(env_list);
		if (!converted_env_list)
			return (errno);
		execve(path_name, cmd, converted_env_list);
		return (0);
	}
	else
	{
		ft_printf("minishell: %s: command not found\n", cmd[0]);
		if (path_name)
			free (path_name);
		return (127);
	}
}
