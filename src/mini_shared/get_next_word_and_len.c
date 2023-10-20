/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_word_and_len.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:54:08 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 12:54:30 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared_internal.h"

static int	is_quote(char c)
{
	if (c == '"' || c == '\'')
		return (1);
	return (0);
}

static int	is_valid_char(char *cmd, int len)
{
	if (ft_isdigit(cmd[len]) && len == 0)
		return (0);
	else if (is_quote(cmd[len]))
		return (0);
	else if (!ft_isalnum(cmd[len]) && cmd[len] != '_')
		return (0);
	return (1);
}

int	get_next_word_len(char *cmd)
{
	int	len;

	len = 0;
	if (cmd[len] == '?')
		return (1);
	while (cmd[len] && is_valid_char(cmd, len))
		len++;
	return (len);
}

char	*get_next_word(char *cmd)
{
	int	len;

	len = get_next_word_len(cmd);
	return (ft_substr(cmd, 0, len));
}
