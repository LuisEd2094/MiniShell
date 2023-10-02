/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:46:04 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 12:47:03 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history_internal.h"

static	t_list	*get_max_input(t_list *head, int size)
{
	t_list	*temp;
	int		i;

	i = size - MAX_LOG_SIZE;
	temp = head;
	while (i-- >= 1)
		temp = temp->next;
	return (temp);
}

void	work_history(int order, char *input)
{
	static t_list	*head = NULL;
	static int		size = 0;

	if (order == INIT)
	{
		ft_read_history(open(HISTORY_FILE, O_RDONLY), &head, &size);
		if (size > MAX_LOG_SIZE)
			add_to_history(get_max_input(head, size));
		else if (head)
			add_to_history(head);
	}
	else if (order == UPDATE)
		update_history(&(head), input, &(size));
	else if (order == CLOSE)
		close_history(head, size, open(HISTORY_FILE, O_WRONLY | O_CREAT, 0644));
}
