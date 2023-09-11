#include "redirections_internal.h"

#include <fcntl.h>
#include <libft.h>

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

int execute_dup2(int fd, int redir_type)
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

int handle_redirection(char *redirection, char *file_name)
{
    int i;
    int redir_type;
    int fd; 
    
    redir_type = get_redir_type(redirection);
    /*
    file_name = get_file_name(&(input[i]), &i);
    if (!file_name)
        return(0);*/
    if (!execute_dup2(open_file(file_name, redir_type), redir_type))
        return (0);
    return (1); 
}

void remove_redir_from_cmds(char **cmds, int i)
{
    int j;
    char    *temp;

    j = i + 2;
    while (cmds[j])
    {
        temp = cmds[i];
        cmds[i] = cmds[j];
        cmds[j] = temp;
        i++;
        j++;
    }

    while (i < j)
    {
        free(cmds[i]);
        cmds[i] = NULL;
        i++;
    }
}

int    check_and_handle_redirections(char **cmds)
{
    int i;

    i = 0;
    while(cmds[i])
    {
        if (cmds[i][0] == '<' || cmds[i][0] == '>')
        {
            handle_redirection(cmds[i], cmds[i + 1]);
            remove_redir_from_cmds(cmds, i);
            i--;
        }
        i++;
    }

    /*

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
    return(1);*/
}