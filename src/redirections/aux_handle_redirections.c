/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux_handle_redirections.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:04:13 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 13:08:53 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections_internal.h"

int	get_redir_type(char *input)
{
	if (input[1] && input[0] == '>' && input[1] == '>')
		return (APPEND_OUTPUT);
	else if (input[0] == '>')
		return (OUTPUT_REDIRECT);
	else
		return (INPUT_REDIRECT);
}

int	read_here_document(t_minishell *mini)
{
	int	fd;
	int	std_fd;

	get_doc_name(mini);
	fd = open(mini->here_doc_name, O_RDONLY);
	std_fd = dup2(fd, STDIN_FILENO);
	close(fd);
	if (std_fd < 0)
		return (0);
	return (1);
}

int	check_and_handle_redirections(char *redir, char *file, t_minishell *mini)
{
	int	i;

	if (redir[0] == '<' && redir[1] == '<')
	{
		read_here_document(mini);

	}	
	else
		handle_redirection(redir, file);
	return (0);
}
