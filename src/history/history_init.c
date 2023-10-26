/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:26:55 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 13:22:01 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history_internal.h"

void	read_from_file(int fd, t_list **head, int *size, char *line)
{
	t_list	*tmp;
	t_list	*new;

	*(size) += 1;
	(*head)->last = *(head);
	tmp = *(head);
	while (line)
	{
		line = get_next_line(fd, 10);
		if (line)
		{
			remove_new_line(line);
			new = ft_lstnew(line);
			if (!new)
				exit(1);
			*(size) += 1;
			tmp->next = new;
			(*head)->last = new;
			tmp = new;
		}
	}
}

t_list	*ft_read_history(int fd, t_list **head, int *size)
{
	char	*line;

	if (fd <= 0)
		return (NULL);
	line = get_next_line(fd, 10);
	if (!line)
		return (NULL);
	remove_new_line(line);
	*(head) = ft_lstnew(line);
	if (!*head)
		exit(1);
	read_from_file(fd, head, size, line);
	close(fd);
	return (NULL);
}
