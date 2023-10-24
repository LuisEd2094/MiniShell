/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 11:48:24 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/18 10:27:18 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execve_internal.h"

char	**conver_env_list(t_list *env_list)
{
	int		i;
	t_list	*temp;
	char	**new;

	i = get_env_list_size(env_list);
	new = (char **)malloc(sizeof(char *) * (i + 1));
	if (!new)
		return (NULL);
	i = 0;
	temp = env_list;
	while (temp)
	{
		new[i] = reconstruct_env(((t_env *)(temp->content))->variable, \
				((t_env *)(temp->content))->value);
		if (!new[i])
			return (free_2d_array(new));
		temp = temp->next;
		i++;
	}
	new[i] = NULL;
	return (new);
}

int	try_execve(char **cmd, t_list *env_list)
{
	char	**converted_env_list;
	char	*path_name;
	int		is_dir;

	if (!cmd || !cmd[0])
		return (0);
	is_dir = 0;
	path_name = check_path_name(cmd, env_list, &is_dir);
	if (path_name && !is_dir)
	{
		converted_env_list = conver_env_list(env_list);
		if (!converted_env_list)
		{
			free(path_name);
			print_perror();
			return (errno);
		}
		execve(path_name, cmd, converted_env_list);
		perror("minishell ");
		exit(EXIT_FAILURE);
	}
	else
		return (no_path_name_found(cmd[0], is_dir));
}
