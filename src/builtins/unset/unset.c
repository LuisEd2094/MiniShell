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
#include <shared.h>
#include <minishell.h>

t_list	*get_env_before(t_list *env_list, t_list *node_to_search)
{
	t_list	*temp;

	temp = env_list;
	while (temp->next)
	{
		if (temp->next == node_to_search)
			return (temp);
		temp = temp->next;
	}
}


static	int remove_node(t_list *env_list, char *str, t_minishell *mini)
{
	t_list	*to_remove;
	t_list	*next;
	t_list	*before;

	if (!str)
		return (0);
	to_remove = get_env_node(env_list, str);
	if (!to_remove)
		return (0);
	if (env_list == to_remove)
	{
		mini->env_list = env_list->next;
		free_node(to_remove);
	}
	else
	{
		before = get_env_before(env_list, to_remove);
		next = to_remove->next;
		before->next = next;
		if (to_remove == env_list->last)
			env_list->last = before;
		free_node(to_remove);
	}
	return (0);
}

int	ft_unset(t_list *env_list, char **cmds, t_minishell *mini)
{
	int i;
	int error;

	i = 1;
	error = 0;
	while (cmds[i])
	{
		if (has_equal(cmds[i]))
		{
			error = print_error("minishell: unset: '", 1);
			error = print_error(cmds[i], 1);
			error = print_error("': not a valid identifier\n", 1);
		}
		else
			remove_node(env_list, cmds[i], mini);
		i++;
	}
	return (error);
}
