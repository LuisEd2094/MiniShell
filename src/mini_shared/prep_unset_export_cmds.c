/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_unset_export_cmds.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:29:06 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/18 10:29:17 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <shared.h>

void	prep_unset_export_commands(char **cmds)
{
	int	i;

	i = -1;
	while (cmds[++i])
	{
		if (!cmds[i][0])
			remove_cmds_from_cmds(cmds, i, 1);
	}
}
