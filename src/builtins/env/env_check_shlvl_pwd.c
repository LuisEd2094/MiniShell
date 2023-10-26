/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_check_shlvl_pwd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:02:19 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/26 16:02:28 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env_internal.h"

void	*check_pwd(t_list *env_list)
{
	t_list	*list_node;
	char	*pwd;
	void	*return_val;

	list_node = get_env_node(env_list, "PWD");
	if (!list_node)
	{
		pwd = getcwd(NULL, 0);
		if (!pwd)
			return (print_perror());
		return_val = create_or_update_env_node(env_list, "PWD", pwd);
		free(pwd);
		if (!return_val)
			return (print_perror());
		return (return_val);
	}
	return ((void *) 1);
}

void	*check_shlvl(t_list	*env_list)
{
	t_list	*list_node;
	t_env	*env_node;
	int		level;

	list_node = get_env_node(env_list, "SHLVL");
	if (!list_node)
		return (create_or_update_env_node(env_list, "SHLVL", "1"));
	else
	{
		env_node = ((t_env *)(list_node->content));
		level = ft_atoi(env_node->value);
		free(env_node->value);
		level++;
		level = check_level(level);
		env_node->value = ft_itoa(level);
		if (!env_node->value)
			return (print_perror());
	}
	return ((void *) 1);
}
