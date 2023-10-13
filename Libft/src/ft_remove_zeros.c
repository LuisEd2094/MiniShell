/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_zeros.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 12:13:43 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 12:13:58 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	remove_zeros(char *str)
{
	int	i;
	int	k;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (str[i] != '0')
		return ;
	k = i;
	while (str[i] == '0')
		i++;
	while (str[i])
		str[k++] = str[i++];
	while (str[k])
		str[k++] = '\0';
}
