#include <minishell.h>

char *get_doc_name(t_minishell *mini)
{
    char *temp_name;

    temp_name = ft_itoa(mini->here_doc_number);
    ft_strlcpy(mini->here_doc_name, "/tmp/tmp_", ft_strlen("/tmp/tmp_") + 1);

    ft_strlcat(mini->here_doc_name, temp_name, ft_strlen(mini->here_doc_name) \
        + ft_strlen(temp_name) + 1);
    mini->here_doc_number++;
    free(temp_name);
}

void    handle_here_document(t_minishell *mini, int i)
{
    int len;
    int fd;
    char    *input;

    mini->here_doc_end = get_next_word(&(mini->input[i]));
    get_doc_name(mini);
    fd = open(mini->here_doc_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
    while (1)
    {
        input = readline(">");
        if (ft_strcmp(input, mini->here_doc_end) == 0)
            break;
        write (fd, input, ft_strlen(input));
        write (fd, "\n", 1);
    }
    close(fd);
    free(mini->here_doc_end);    
}

void    parse_input(t_minishell *mini)
{
    int i;

    i = 0;
    while (mini->input[i])
    {
        if (mini->input[i] == '<' && mini->input[i + 1] == '<')
            handle_here_document(mini, i + 2 + get_white_space_size(&mini->input[i + 2]));
        i++;
    }
    mini->here_doc_number = 0;
    return; 
}