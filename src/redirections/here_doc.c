/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 13:09:41 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 13:14:50 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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
	while (1)
	{
		get_doc_name(mini);
		if (access(mini->here_doc_name, F_OK) != -1)
			unlink(mini->here_doc_name);
		else
		{
			mini->here_doc_number = 0;
			break ;
		}
	}
}

static char	*check_input(char *input, t_minishell *mini)
{
	int		i;
	char	*env;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && is_ascii_no_space(input[i + 1]))
		{
			env = get_env_str(get_next_word(&input[i + 1]), mini->env_list);
			input = ft_replace(input, env, i, 1);
		}
		i++;
	}
	return (input);
}

void	handle_here_document(t_minishell *mini, int i)
{
	int		fd;
	char	*input;

	mini->here_doc_end = get_next_word(&(mini->input[i]));
	get_doc_name(mini);
	fd = open(mini->here_doc_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		input = readline(">");
		if (ft_strcmp(input, mini->here_doc_end) == 0)
			break ;
		input = check_input(input, mini);
		write (fd, input, ft_strlen(input));
		write (fd, "\n", 1);
		free(input);
	}
	close(fd);
	free(mini->here_doc_end);
}

void	create_here_doc(t_minishell *mini)
{
	int	i;

	i = 0;
	while (mini->input[i])
	{
		if (mini->input[i] == '<' && mini->input[i + 1] == '<')
			handle_here_document(mini, i + 2 + \
					get_white_space_size(&mini->input[i + 2]));
		i++;
	}
	mini->here_doc_number = 0;
}
