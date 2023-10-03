/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:49:15 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 10:50:39 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
// need to check if the node is the first one
t_list	*get_env_before(t_list *env_list, char *str)
{
	t_list	*temp;

	temp = env_list;
	if (ft_strcmp(((t_env *)(temp->content))->variable, str) == 0)
		return (temp);
	while (temp->next)
	{
		if (ft_strcmp(((t_env *)(temp->next->content))->variable, str) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	free_temp(t_list *temp)
{
	free(((t_env *)(temp->content))->value);
	free(((t_env *)(temp->content))->variable);
	free(((t_env *)(temp->content)));
	free(temp);
}

t_list	*ft_unset(t_list *env_list, char *str)
{
	t_list	*temp;
	t_list	*next;
	t_list	*before;

	if (!str)
		return (0);
	temp = get_env_node(env_list, str);
	before = get_env_before(env_list, str);
	if (!before)
		return (0);
	next = temp->next;
	if (env_list == before)
	{
		next->last = env_list->last;
		env_list = next;
	}
	free_temp(temp);
	if (next)
		before->next = next;
	else
	{
		before->next = NULL;
		env_list->last = before;
	}
	return (env_list);
}
