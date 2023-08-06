/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 09:46:11 by lsoto-do          #+#    #+#             */
/*   Updated: 2022/11/09 10:56:43 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **last, t_list *new)
{
	if (*last == NULL)
	{
		*last = new;
		return ;
	}
	new->next = *last;
	*last = new;
}
