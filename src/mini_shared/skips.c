/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skips.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 13:35:49 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 13:36:16 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shared_internal.h"

int	get_quotes_size(char *input)
{
	char	quote;
	int		i;

	i = 0;
	quote = input[i];
	i++;
	while (input[i] && input[i] != quote)
		i++;
	if (input[i] == quote)
		i++;
	if (input[i] == '\0' || input[i] == ' ')
		return (i);
	if (input[i] == '"' || input[i] == '\'')
		i += get_quotes_size(&input[i]);
	i += get_arg_size_skip_redirections(&input[i]);
	return (i);
}

int	get_white_space_size(char *input)
{
	int	i;

	i = 0;
	while (input[i] && ft_isspace(input[i]))
		i++;
	return (i);
}

int	get_arg_size_skip_redirections(char *input)
{
	int	i;

	i = 0;
	while (input[i] && is_ascii_no_space(input[i]) && \
	!(input[i] == '>' || input[i] == '<'))
	{
		if (input[i] == '"' || input[i] == '\'')
			i += get_quotes_size(&input[i]);
		else
			i++;
	}
	return (i);
}

int	get_redirection_size(char *input)
{
	int		i;
	char	symbol;

	i = 0;
	symbol = input[i];
	if (input[i + 1] && input[i + 1] == symbol)
		return (2);
	else
		return (1);
}
