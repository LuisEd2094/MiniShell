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
		return (-1);
	}
	if (!old_dir[0])
	{
		free(old_dir);
		return (print_error("minishell: cd: OLDPWD not set\n", 1));
	}
	if (chdir(old_dir) == -1)
	{
		free(old_dir);
		perror("Error al cambiar al antiguo directorio");
		return (-1);
	}
	return (0);
}
