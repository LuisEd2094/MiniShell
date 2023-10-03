/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:38:14 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 10:48:27 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <shared.h>

int	ft_print_env(char **cmds, t_list *env_list)
{
	t_list	*temp;

	if (cmd_len(cmds) > 1)
		return (print_error("env : invalid usage\n", 1));
	if (!env_list->content)
		return (0);
	temp = env_list;
	while (temp)
	{
		if (((t_env *)(temp->content))->assigned)
			ft_printf("%s=%s\n", ((t_env *)(temp->content))->variable, \
		((t_env *)(temp->content))->value);
		temp = temp->next;
	}
	return (0);
}

void	free_env_list(t_list *env_list)
{
	t_list	*next;
	t_list	*cursor;

	cursor = env_list;
	while (cursor)
	{
		next = cursor->next;
		free(((t_env *)(cursor->content))->variable);
		free(((t_env *)(cursor->content))->value);
		free((cursor->content));
		free(cursor);
		cursor = next;
	}
}

t_list	*iter_env(char *env)
{
	t_list	*new;
	t_env	*env_node;

	env_node = create_env_node(env);
	if (!env_node)
		exit(1);
	new = ft_lstnew(env_node);
	if (!new)
		exit (1);
	return (new);
}

t_list	*init_env(char **env)
{
	t_list	*env_list;
	t_list	*tmp;
	t_env	*env_node;
	int		i;

	if (!env[0])
		env_node = NULL;
	else 
		env_node = create_env_node(env[0]);
	env_list = ft_lstnew(env_node);
	if (!env_list)
		exit(1);
	env_list->last = env_list;
	if (!env[0])
		return(env_list);
	tmp = env_list;
	i = 1;
	while (env[i])
	{
		tmp->next = iter_env(env[i]);
		tmp = tmp->next;
		env_list->last = tmp;
		i++;
	}
	return (env_list);
}
