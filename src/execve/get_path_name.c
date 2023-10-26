/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path_name.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:07:20 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/26 16:07:22 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve_internal.h"

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
		return (no_list());
	i = 0;
	while (path_list[i])
	{
		if (path_list[i][ft_strlen(path_list[i])] != '/')
			path_name = join_path(path_list[i], cmd[0]);
		else
			path_name = ft_strjoin(path_list[i], cmd[0]);
		if (!path_name)
			return (free_2d_array(path_list));
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

int	check_if_is_dir(char *path)
{
	struct stat	file_info;

	if (stat(path, &file_info) == 0)
	{
		if (S_ISDIR(file_info.st_mode))
			return (1);
		else
			return (0);
	}
	return (1);
}

char	*check_path_name(char **cmd, t_list *env_list, int *is_dir)
{
	if (cmd[0] && cmd[0][0] == '\0')
		return (NULL);
	else if (ft_strnstr(cmd[0], "/", ft_strlen(cmd[0])) != NULL)
	{
		*is_dir = check_if_is_dir(cmd[0]);
		if (*is_dir)
			return (NULL);
		if (access(cmd[0], F_OK) != -1 && access(cmd[0], X_OK) != -1)
			return (cmd[0]);
		return (NULL);
	}
	else
		return (get_path_name(cmd, \
	get_paths(get_env_node(env_list, "PATH"))));
}
