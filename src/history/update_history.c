/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:45:27 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 13:22:17 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history_internal.h"

void	update_list(int *size, t_list **head, t_list *new)
{
	t_list	*temp;

	if (*(size) == 0)
	{
		*head = new;
		(*head)->last = new;
	}
	else
	{
		temp = (*head)->last;
		temp->next = new;
		(*head)->last = new;
	}
}

void	update_history(t_list **head, char *input, int *size)
{
	t_list	*new;
	char	*content;

	if ((*head) && ft_strcmp((*head)->last->content, input) == 0)
		return ;
	remove_new_line(input);
	content = ft_strdup(input);
	if (!content)
		return ;
	new = ft_lstnew(content);
	if (!new)
		exit(1);
	update_list(size, head, new);
	*(size) += 1;
	add_history(input);
}
