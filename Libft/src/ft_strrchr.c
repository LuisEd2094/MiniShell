/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 19:10:13 by lsoto-do          #+#    #+#             */
/*   Updated: 2022/11/09 10:55:22 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*str;
	char	h;

	str = (char *)s;
	i = ft_strlen(s);
	h = c;
	while (i >= 0)
	{
		if (str == 0)
			return (NULL);
		if (str == NULL)
			return (str);
		if (str[i] == h)
			return (str + i);
		i--;
	}
	return (NULL);
}
