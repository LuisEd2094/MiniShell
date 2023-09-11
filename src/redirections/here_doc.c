#include <minishell.h>

char *get_doc_name(t_minishell *mini)
{
    char *temp_name;

    temp_name = ft_itoa(mini->here_doc_number);
    ft_strlcpy(mini->here_doc_name, TEMP_FILE_NAME, ft_strlen(TEMP_FILE_NAME) + 1);

    ft_strlcat(mini->here_doc_name, temp_name, ft_strlen(mini->here_doc_name) \
        + ft_strlen(temp_name) + 1);
    mini->here_doc_number++;
    free(temp_name);
}

void    delete_temp_files(t_minishell *mini)
{
    while(1)
    {
        get_doc_name(mini);
        if (access(mini->here_doc_name, F_OK) !=  -1)
        {
            unlink(mini->here_doc_name);
            mini->here_doc_number++;
        }
        else
        {
            mini->here_doc_number = 0;
            break;
        }    
    }
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