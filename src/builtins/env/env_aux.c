/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:56:28 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 11:57:03 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_internal.h"

void	print_shlvl_high(char *lvl)
{
	write(STDERR_FILENO,"minishell: warning: shell level (", \
	ft_strlen("minishell: warning: shell level ("));
	write(STDERR_FILENO, lvl, ft_strlen(lvl));
	write(STDERR_FILENO,") too high, resetting to 1\n", \
	ft_strlen(") too high, resetting to 1\n"));
}

t_env	*check_shlvl(t_env	*node)
{
	int		level;
	char	*str;

	if (ft_strcmp(node->variable, "SHLVL") == 0)
	{
		level = ft_atoi(node->value);
		free(node->value);
		level++;
		if (level >= 1000)
		{
			str = ft_itoa(level);
			print_shlvl_high(str);
			free(str);
			level = 0;
		}
		node->value = ft_itoa(level);
		if (!node->value)
			return (NULL);
	}
	return (node);
}

t_list	*iter_env(char *env)
{
	t_list	*new;
	t_env	*env_node;

	env_node = create_new_env_node(env);
	if (!env_node)
		return (NULL);
	env_node = check_shlvl(env_node);
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

t_list	*fill_up_env_list(t_list *env_list, char **env)
{
	int		i;
	t_list	*tmp;

	tmp = env_list;
	i = 1;
	while (env[i])
	{
		tmp->next = iter_env(env[i]);
		if (!tmp->next)
			break ;
		tmp = tmp->next;
		env_list->last = tmp;
		i++;
	}
	return (env_list);
}

t_list	*create_empty_list(void)
{
	t_list	*env_list;

	env_list = ft_lstnew(NULL);
	if (!env_list)
		exit (EXIT_FAILURE);
	return (env_list);
}
