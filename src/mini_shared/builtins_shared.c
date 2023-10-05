/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_shared.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:50:07 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 12:51:14 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>

t_list	*get_env_node(t_list *env_list, char *str)
{
	t_list	*temp;

	temp = env_list;
	while (temp)
	{
		if (ft_strcmp(((t_env *)(temp->content))->variable, str) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
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

t_env	*create_env_node(char *variable, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		exit (1);
	new->variable = variable;
	new->value = value;
	if (value && value[0])
		new->assigned = 1;
	else
		new->assigned = 0;
	return (new);
}

t_list		*add_new_env(t_list *env_list, char *variable, char *value)
{
	t_list	*new;
	t_env	*env_node;

	env_node = create_env_node(variable, value);
	if (!env_list->content)
		env_list->content = env_node;
	else
	{
		new = ft_lstnew(env_node);
		env_list->last->next = new;
		env_list->last = new;
	}
	return (new);
}

void	update_env_value(char *env_node_str, char *str)
{
	int		i;
	char	*new;

	free(env_node_str);
	ft_strlcpy(env_node_str, str, ft_strlen(str));
	i = ft_strlen(str);
	new = (char *)malloc(sizeof(char) * i + 1);
	if (!new)
		exit(0);
	i = -1;
	while (str[++i])
		new[i] = str[i];
	new[i] = '\0';
	env_node_str = new;
}
