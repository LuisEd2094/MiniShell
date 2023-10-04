/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:26:15 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 12:26:25 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history_internal.h"


void	add_to_history(t_list *node)
{
	t_list	*temp;

	temp = node;
	while (temp)
	{
		add_history(temp->content);
		temp = temp->next;
	}
}
