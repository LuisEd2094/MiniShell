/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_aux.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:17:54 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/18 10:20:00 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cd_internal.h"

int	execute_change_old_dir(char *old_dir)
{
	if (!old_dir)
	{
		perror("minishell ");
		return (errno);
	}
	if (!old_dir[0])
	{
		free(old_dir);
		return (print_error("minishell: cd: OLDPWD not set\n", 1));
	}
	if (chdir(old_dir) == -1)
	{
		free(old_dir);
		return (print_error("minishell: cd: Error in OLDPWD\n", 1));
	}
	ft_printf("%s\n", old_dir);
	free(old_dir);
	return (0);
}

void	new_pwd(t_list *env_list)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return ;
	create_or_update_env_node(env_list, "PWD", pwd);
	free(pwd);
}
