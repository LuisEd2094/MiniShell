/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:49:15 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 12:08:54 by lsoto-do         ###   ########.fr       */
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
	return (NULL);
}

static	void	remove_head(t_minishell *mini, t_list *to_remove)
{
	if (!mini->env_list->next)
	{
		free_env_node(mini->env_list->content);
		mini->env_list->content = NULL;
	}
	else
	{
		mini->env_list = to_remove->next;
		free_node(to_remove);
	}
}

void	remove_node(char *str, t_minishell *mini)
{
	t_list	*to_remove;
	t_list	*next;
	t_list	*before;

	if (!str)
		return ;
	to_remove = get_env_node(mini->env_list, str);
	if (!to_remove)
		return ;
	if (mini->env_list == to_remove)
		remove_head(mini, to_remove);
	else
	{
		before = get_env_before(mini->env_list, to_remove);
		next = to_remove->next;
		before->next = next;
		if (to_remove == mini->env_list->last)
			mini->env_list->last = before;
		free_node(to_remove);
	}
}

int	ft_unset(char **cmds, t_minishell *mini)
{
	int	i;
	int	error;

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
			remove_node(cmds[i], mini);
		i++;
	}
	return (error);
}
