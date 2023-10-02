/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_internal.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:14:36 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 13:15:18 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTIONS_INTERNAL_H
# define REDIRECTIONS_INTERNAL_H
# include <minishell.h>

typedef enum s_redir_type
{
	INPUT_REDIRECT = 1,
	HERE_DOCUMENT,
	OUTPUT_REDIRECT,
	APPEND_OUTPUT,
}	t_redir_type;

int		get_redir_type(char *input);
char	*get_doc_name(t_minishell *mini);
int		handle_redirection(char *redirection, char *file_name);
void	remove_redir_from_cmds(char **cmds, int i);

#endif
