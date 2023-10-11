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
<<<<<<< HEAD
=======
#include <minishell.h>
>>>>>>> lsoto-do

int	ft_print_env(char **cmds, t_list *env_list)
{
	t_list	*temp;

<<<<<<< HEAD
	if (cmd_len(cmds) > 1)
		return (print_error("env : invalid usage\n", 1));
=======
	if (cmds[1])
		return (print_error("minishell : env: invalid usage\n", 1));
>>>>>>> lsoto-do
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
<<<<<<< HEAD

	cursor = env_list;
	while (cursor)
	{
		next = cursor->next;
		free(((t_env *)(cursor->content))->variable);
		free(((t_env *)(cursor->content))->value);
		free((cursor->content));
		free(cursor);
		cursor = next;
=======

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
	free(tab);
	if (!env_node)
	{
		free(tab[0]);
		free(tab[1]);
		return (print_perror());
>>>>>>> lsoto-do
	}
	return (env_node);
}

t_list	*iter_env(char *env)
{
	t_list	*new;
	t_env	*env_node;
<<<<<<< HEAD

	env_node = create_env_node(env);
=======
	char	**tab;

	env_node = create_new_env_node(env);
>>>>>>> lsoto-do
	if (!env_node)
		return (NULL);
	new = ft_lstnew(env_node);
	if (!new)
<<<<<<< HEAD
		exit (1);
=======
	{
		free_env_node(env_node);
		return (print_perror());
	}
>>>>>>> lsoto-do
	return (new);
}

t_list	*fill_up_env_list(t_list *env_list, char **env)
{
	int		i;
	t_list	*tmp;

<<<<<<< HEAD
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
=======
>>>>>>> lsoto-do
	tmp = env_list;
	i = 1;
	while (env[i])
	{
		tmp->next = iter_env(env[i]);
<<<<<<< HEAD
=======
		if (!tmp->next)
			break ;
>>>>>>> lsoto-do
		tmp = tmp->next;
		env_list->last = tmp;
		i++;
	}
	return (env_list);
<<<<<<< HEAD
}
=======
}

t_list	*init_env(char **env)
{
	t_list	*env_list;
	t_env	*env_node;

	if (!env[0])
	{
		env_list = ft_lstnew(NULL);
		if (!env_list)
			exit(EXIT_FAILURE);
		return (env_list);
	}
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
		return(env_list);
	return (fill_up_env_list(env_list, env));
}
>>>>>>> lsoto-do
