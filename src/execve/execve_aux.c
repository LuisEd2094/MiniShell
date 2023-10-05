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

void	free_path_list(char **path_list)
{
	int	i;

	i = 0;
	while (path_list[i])
		free(path_list[i++]);
	free(path_list);
}

char	*join_path(char *path_list, char *cmd)
{
	char	*temp_path;
	char	*path_name;

	temp_path = ft_strjoin(path_list, "/");
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
		exit(1);
	new = ft_strjoin(temp, value);
	free(temp);
	if (!new)
		exit (1);
	return (new);
}
