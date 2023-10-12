/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_single_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:52:35 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 12:53:08 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

char	**ft_single_split(char const *s, char c)
{
	char	**tab;
	int		i;
	int		j;

	tab = (char **)malloc(sizeof(char *) * 3);
	if (!tab)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != c)
		i++;
	tab[0] = (char *)malloc(sizeof(char) * (i + 1));
	if (!tab[0])
	{
		free(tab);
		return (NULL);
	}
	j = i;
	while (s[i])
		i++;
	tab[1] = (char *)malloc(sizeof(char) * ((i - j) + 1));
	if (!tab[1])
		return (free_2d_array(tab));
	i = 0;
	while (i < j)
	{
		tab[0][i] = s[i];
		i++;
	}
	tab[0][i] = '\0';
	i = 0;
	while (s[j])
	{
		j++;
		tab[1][i] = s[j];
		i++;
	}
	tab[1][i] = '\0';
	tab[2] = NULL;
	return (tab);
}
