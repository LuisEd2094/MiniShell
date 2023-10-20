/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:56:28 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/18 10:24:22 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_internal.h"

void	print_shlvl_high(char *lvl)
{
	write(STDERR_FILENO, "minishell: warning: shell level (", \
	ft_strlen("minishell: warning: shell level ("));
	write(STDERR_FILENO, lvl, ft_strlen(lvl));
	write(STDERR_FILENO, ") too high, resetting to 1\n", \
	ft_strlen(") too high, resetting to 1\n"));
}

int	check_level(int level)
{
	char	*str;

	if (level >= 1000)
	{
		str = ft_itoa(level);
		print_shlvl_high(str);
		free(str);
		level = 0;
	}
	if (level < 0)
		level = 0;
	return (level);
}

t_env	*check_shlvl(t_list	*env_list)
{
	t_list	*list_node;
	t_env	*env_node;
	int		level;

	list_node = get_env_node(env_list, "SHLVL");
	if (!list_node)
		return (create_or_update_env_node(env_list, "SHLVL", "0"));
	else
	{
		env_node = ((t_env *)(list_node->content));
		level = ft_atoi(env_node->value);
		free(env_node->value);
		level++;
		level = check_level(level);
		env_node->value = ft_itoa(level);
		if (!env_node->value)
			return (NULL);
	}
	return ((void *) 1);
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