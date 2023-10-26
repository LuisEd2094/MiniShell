/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:38:14 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 11:56:20 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_internal.h"

int	ft_print_env(char **cmds, t_list *env_list)
{
	t_list	*temp;
	t_env	*node;

	node = NULL;
	if (cmds[1])
		return (print_error("minishell : env: invalid usage\n", 1));
	if (!env_list->content)
		return (0);
	temp = env_list;
	while (temp)
	{
		node = ((t_env *)(temp->content));
		if (node->assigned && ft_strcmp("?", node->variable) != 0)
			ft_printf("%s=%s\n", node->variable, \
		node->value);
		temp = temp->next;
	}
	return (0);
}

t_list	*iter_env(char *env)
{
	t_list	*new;
	t_env	*env_node;

	env_node = create_new_env_node(env);
	if (!env_node)
		return (NULL);
	new = ft_lstnew(env_node);
	if (!new)
	{
		free_env_node(env_node);
		return (print_perror());
	}
	return (new);
}

void	free_env_list(t_list *env_list)
{
	t_list	*next;
	t_list	*cursor;

	cursor = env_list;
	while (cursor)
	{
		next = cursor->next;
		free_node(cursor);
		cursor = next;
	}
	free(cursor);
}

t_env	*create_new_env_node(char *env)
{
	t_env	*env_node;
	char	**tab;

	tab = ft_single_split(env, '=');
	if (!tab)
		return (print_perror());
	env_node = create_env_node(tab[0], tab[1]);
	free_2d_array(tab);
	if (!env_node)
		return (print_perror());
	if (has_equal(env))
		env_node->assigned = 1;
	return (env_node);
}

t_list	*init_env(char **env)
{
	t_list	*env_list;
	t_env	*env_node;

	if (!env[0])
		return (create_empty_list());
	env_node = create_new_env_node(env[0]);
	if (!env_node)
		return (print_perror());
	env_list = ft_lstnew(env_node);
	if (!env_list)
	{
		free_env_node(env_node);
		return (print_perror());
	}
	env_list->last = env_list;
	if (!env[0])
		return (env_list);
	return (fill_up_env_list(env_list, env));
}
