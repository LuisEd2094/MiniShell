#include "redirections_internal.h"
/*
int close_redirections(t_minishell *mini)
{
    dup2(mini->og_in, STDIN_FILENO);
    dup2(mini->og_out, STDOUT_FILENO);
    return (1);
}

int open_file(char *file_name, int redir_type)
{
    int fd;

    if (redir_type == INPUT_REDIRECT)
    {
        if (access(file_name, R_OK) != 0)
            return(print_error(file_name));
    }
    if (redir_type == INPUT_REDIRECT)
        fd = open(file_name, O_RDONLY);
    else if (redir_type == OUTPUT_REDIRECT)
        fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
    else if (redir_type == APPEND_OUTPUT)
        fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
    else
        ft_printf("Should handle logic for Here document \n");
    if (fd < 0)
        return (print_error(file_name));
    return (fd);
}

int execute_dup2(int fd, int redir_type, t_minishell *mini)
{
    int std_fd;

    if (redir_type == OUTPUT_REDIRECT || redir_type == APPEND_OUTPUT)
    {
        std_fd = dup2(fd, STDOUT_FILENO);
        close(fd);

    }
    else
    {    
        std_fd = dup2(fd, STDIN_FILENO);
        close(fd);
    }
    if (std_fd < 0)
        return (0);
    return (1);
}

int handle_redirection(char *input, int *start, t_minishell *mini)
{
    int i;
    char *file_name;
    int redir_type;
    int fd; 
    
    i = get_starting_pos(input);
    redir_type = get_redir_type(input);
    file_name = get_file_name(&(input[i]), &i);
    if (!file_name)
        return(0);
    if (!execute_dup2(open_file(file_name, redir_type), redir_type, mini))
        return (0);
    *start += i;
    return (1); 
}


int    check_and_handle_redirections(t_minishell *mini, int start, int end)
{
    char *input;

    input = mini->input;
    if (input [start] == '|')
        start++;
    while (input[start] && start <= end)
    {
        while(input[start] && start <= end && (input[start] != '>' && input[start] != '<'))
            start++;
        if (input[start] == '>' || input[start] == '<')
        {
            if (!handle_redirection(&input[start], &start, mini))
                return (0);
        }
    }
    return(1);
}*/