/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 10:22:43 by lsoto-do          #+#    #+#             */
/*   Updated: 2022/11/09 10:58:19 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	void	*temp;
	t_list	*new;
	t_list	*elem;

	if (!lst)
		return (0);
	new = NULL;
	while (lst)
	{
		temp = f(lst->content);
		elem = ft_lstnew(temp);
		if (!elem)
		{
			del(temp);
			ft_lstclear(&new, del);
		}
		ft_lstadd_back(&new, elem);
		lst = lst->next;
	}
	return (new);
}
