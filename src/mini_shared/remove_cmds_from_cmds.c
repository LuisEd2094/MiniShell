/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_cmds_from_cmds.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:29:26 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/18 10:29:30 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	remove_cmds_from_cmds(char **cmds, int i, int next_valid)
{
	int		j;
	char	*temp;

	j = i + next_valid;
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
