/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_node.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:27:25 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 13:27:35 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_env_node(t_env *env_node)
{
	if (!env_node)
		return ;
	free(env_node->value);
	free(env_node->variable);
	free(env_node);
}

void	free_node(t_list *temp)
{
	free_env_node(temp->content);
	free(temp);
}
