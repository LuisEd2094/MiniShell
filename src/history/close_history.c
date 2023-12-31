/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:19:52 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 13:20:01 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history_internal.h"

void	ft_close_history(t_list *head, int size, int fd)
{
	t_list	*temp;
	int		i;

	temp = head;
	if (size > MAX_FILE_LOG_SIZE)
	{
		i = size - MAX_FILE_LOG_SIZE;
		while (i-- >= 1)
			temp = temp->next;
	}
	while (temp)
	{
		ft_putendl_fd((char *)(temp->content), fd);
		temp = temp->next;
	}
	close(fd);
	ft_lstclear(&(head), free);
}
