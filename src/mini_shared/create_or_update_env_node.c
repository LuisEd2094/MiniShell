/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_or_add_env_node.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:51:24 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 12:52:25 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*create_or_update_env_node(t_list *env_list, char *variable, char *value)
{
	t_list	*temp;

	temp = get_env_node(env_list, variable);
	if (!temp)
	{
		if (!add_new_env(env_list, variable, value))
			return (NULL);
	}
	else
	{		
		free(((t_env *)(temp->content))->value);
		((t_env *)(temp->content))->value = value;
		free(variable);
		if (value[0])
			((t_env *)(temp->content))->assigned = 1;
		else
			((t_env *)(temp->content))->assigned = 0;
	}
	return ((void *) 1);
}
