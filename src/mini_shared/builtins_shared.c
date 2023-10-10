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
#include <shared.h>

t_list	*get_env_node(t_list *env_list, char *str)
{
	t_list	*temp;

	temp = env_list;
	while (temp)
	{
		if (ft_strncmp(((t_env *)(temp->content))->variable, str, ft_strlen(str) + 1) == 0)
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
	new->variable = variable;
	new->value = value;
	if (value && value[0])
		new->assigned = 1;
	else
		new->assigned = 0;
	return (new);
}

void	*add_new_env(t_list *env_list, char *variable, char *value)
{
	t_env	*env_node;
	t_list *temp;

	env_node = create_env_node(variable, value);
	if (!env_node)
		return (print_perror());
	if (!env_list->content)
		env_list->content = env_node;
	else
	{
		temp = env_list;
		while(temp->next)
			temp = temp->next;
		temp->next = ft_lstnew(env_node);
	}
}

bool has_equal(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}
