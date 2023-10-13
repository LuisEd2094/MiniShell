/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_or_add_env_node.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:51:24 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 13:27:16 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_plus(char *var)
{
	if (var[ft_strlen(var) - 1] == '+')
		return (1);
	else
		return (0);
}

static int	size(char *og_val, char *new_val)
{
	return (ft_strlen(og_val) + ft_strlen(new_val) + 1);
}

void	*update_node(t_env *env_node, char *value, int plus)
{
	char	*new;

	if (plus)
	{
		new = (char *)malloc(sizeof(char) * size(env_node->value, value));
		if (!new)
			return (print_perror);
		ft_strlcpy(new, (env_node->value), ft_strlen(env_node->value) + 1);
		ft_strlcat(new, value, ft_strlen(new) + ft_strlen(value) + 1);
		free(env_node->value);
		env_node->value = new;
	}
	else
	{
		new = (char *)malloc(sizeof(char ) * ft_strlen(value) + 1);
		if (!env_node->value)
			return (print_error);
		ft_strlcpy(env_node->value, value, ft_strlen(value) + 1);
	}
	if (value[0])
		env_node->assigned = 1;
	else
		env_node->assigned = 0;
	return ((void *)1);
}

void	*create_or_update_env_node(t_list *env_list, char *var, char *value)
{
	t_list	*temp;
	int		has_plus;

	has_plus = check_plus(var);
	if (has_plus)
		var[ft_strlen(var) - 1] = '\0';
	temp = get_env_node(env_list, var);
	if (!temp)
	{
		if (!add_new_env(env_list, var, value))
			return (NULL);
	}
	else
	{
		if (!update_node(temp->content, value, has_plus))
			return (NULL);
	}
	return ((void *) 1);
}
