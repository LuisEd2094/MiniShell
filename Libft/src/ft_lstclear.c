/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:14:56 by lsoto-do          #+#    #+#             */
/*   Updated: 2022/11/09 10:57:38 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*cur;

	if (!del || !lst || !(*lst))
		return ;
	while (*lst != NULL)
	{
		cur = *lst;
		*lst = cur->next;
		if (cur->content != NULL)
			del((cur->content));
		del(cur);
	}
	*lst = NULL;
}
