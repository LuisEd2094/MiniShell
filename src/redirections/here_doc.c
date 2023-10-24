/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:09:41 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/18 13:05:39 by gmacias-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redirections_internal.h"

void	get_doc_name(t_minishell *mini)
{
	char	*temp_name;

	temp_name = ft_itoa(mini->here_doc_number);
	ft_strlcpy(mini->here_doc_name, TEMP_FILE_NAME, \
			ft_strlen(TEMP_FILE_NAME) + 1);
	ft_strlcat(mini->here_doc_name, temp_name, ft_strlen(mini->here_doc_name) \
		+ ft_strlen(temp_name) + 1);
	mini->here_doc_number++;
	free(temp_name);
}

void	delete_temp_files(t_minishell *mini)
{
	int	i;

	while (1)
	{
		i = 0;
		get_doc_name(mini);
		if (access(mini->here_doc_name, F_OK) != -1)
			unlink(mini->here_doc_name);
		else
		{
			mini->here_doc_number = 0;
			break ;
		}
		while (i < 200)
			mini->here_doc_name[i++] = '\0';
	}
}

int	create_here_doc(t_minishell *mini)
{
	int	i;
	int	j;
	int	status;

	i = 0;
	status = 0;
	while (mini->cmds[i])
	{
		j = 0;
		while (mini->cmds[i][j])
		{
			if (mini->cmds[i][j][0] == '<' && mini->cmds[i][j][1] == '<')
			{
				check_here_doc_end(mini, mini->cmds[i][j + 1]);
				status = handle_here_document(mini);
				if (status)
					return (status);
				j++;
			}
			j++;
		}
		i++;
	}
	mini->here_doc_number = 0;
	return (status);
}
