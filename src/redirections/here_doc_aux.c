#include "redirections_internal.h"

static char	*check_input(char *input, t_minishell *mini)
{
	int		i;
	char	*env;

	i = 0;
	while (input[i])
	{
		if (input[i] == '$' && input[i + 1] && input[i + 1] != '$' && \
				ft_isprint(input[i + 1]) && !ft_isspace(input[i + 1]))
		{
			env = get_env_str(get_next_word(&input[i + 1]), mini->env_list);
			input = ft_replace(input, env, i, 1);
			i += ft_strlen(env);
			free(env);
		}
		else
			i++;
	}
	return (input);
}

int	handle_here_document(t_minishell *mini)
{
	int		fd;
	char	*input;

	get_doc_name(mini);
	fd = open(mini->here_doc_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
	while (!g_received_signal)
	{
		input = readline(">");
		if (!input)
			break ;
		if (ft_strcmp(input, mini->here_doc_end) == 0)
			break ;
		if (!mini->here_quotes)
			input = check_input(input, mini);
		write (fd, input, ft_strlen(input));
		write (fd, "\n", 1);
		free(input);
		input = NULL;
	}
	if (input)
		free(input);
	close(fd);
	if (g_received_signal)
		return (g_received_signal);
	return (0);
}

void	check_here_doc_end(t_minishell *mini, char *end)
{
	int i;

	mini->here_quotes = ft_strnstr(end, "\"", ft_strlen(end)) != NULL;
	if (mini->here_quotes)
	{
		i = 0;
		while (end[i])
		{
			if (end[i] == '\'' || end[i] == '"')
				i = remove_quote(end, end[i], i);
			else
				i++;
		}	
	}
	mini->here_doc_end = end;
}