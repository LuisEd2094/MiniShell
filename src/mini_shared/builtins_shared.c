/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_shared.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:25:00 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 13:26:04 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <shared.h>

t_list	*get_env_node(t_list *env_list, char *str)
{
	t_list	*temp;

	if (!env_list->content)
		return (NULL);
	temp = env_list;
	while (temp && (t_env *)(temp->content))
	{
		if (ft_strcmp(((t_env *)(temp->content))->variable, str) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

t_env	*create_env_node(char *variable, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->variable = (char *)malloc(sizeof(char) * ft_strlen(variable) + 1);
	if (!new->variable)
	{
		free(new);
		return (NULL);
	}
	new->value = (char *)malloc(sizeof(char) * ft_strlen(value) + 1);
	if (!new->value)
	{
		free(new->variable);
		free(new);
		return (NULL);
	}
	ft_strlcpy(new->variable, variable, ft_strlen(variable) + 1);
	ft_strlcpy(new->value, value, ft_strlen(value) + 1);
	if (value && value[0])
		new->assigned = 1;
	else
		new->assigned = 0;
	return (new);
}

void	*add_new_env(t_list *env_list, char *variable, char *value)
{
	t_env	*env_node;
	t_list	*temp;

	env_node = create_env_node(variable, value);
	if (!env_node)
		return (print_perror());
	if (!env_list->content)
		env_list->content = env_node;
	else
	{
		temp = env_list;
		while (temp->next)
			temp = temp->next;
		temp->next = ft_lstnew(env_node);
		if (!temp->next)
			return (print_perror());
	}
	return ((void *) 1);
}

bool	has_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
