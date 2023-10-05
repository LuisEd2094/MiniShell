/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_or_add_env_node.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:51:24 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 12:52:25 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	free_tab_export(char **tab)
{
	if (tab[0])
		free(tab[0]);
	if (tab[1])
		free(tab[1]);
	if (tab)
		free(tab);
}

void	create_or_update_env_node(t_list *env_list, char *variable, char *value)
{
	t_list	*temp;

	temp = get_env_node(env_list, variable);
	if (!temp)
	{
		add_new_env(env_list, variable, value);
	}
	else
	{		
		free(((t_env *)(temp->content))->value);
		((t_env *)(temp->content))->value = (char *)malloc(sizeof(char) * \
		(ft_strlen(value) + 1));
		ft_strlcpy(((t_env *)(temp->content))->value, value, \
				ft_strlen(value) + 1);
		if (value[0])
			((t_env *)(temp->content))->assigned = 1;
		else
			((t_env *)(temp->content))->assigned = 0;
	}
}
