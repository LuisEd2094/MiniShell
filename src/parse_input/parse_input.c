#include <minishell.h>

void example_of_heredoc(t_minishell *mini)
{

    get_doc_name(mini);
    int fd = open(mini->here_doc_name, O_RDONLY);
    dup2(fd, STDIN_FILENO);

    char *cat[2];
    cat[0] = "cat";
    cat[1] = NULL;
    execve("/usr/bin/cat", cat, NULL);
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
    example_of_heredoc(mini);
    return; 
}