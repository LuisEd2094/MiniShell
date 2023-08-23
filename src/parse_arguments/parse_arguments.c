#include <minishell.h>
#include "parse_internal.h"


#include <unistd.h>



char   *get_file_name(char *input, int *i)
{
    char    *new;
    int     j;
    int     k;

    j = get_ascii_size(input);
    new = (char *)malloc(sizeof(char) * j + 1);
    if (!new)
        return(NULL);
    ft_strlcpy(new, input, j + 1);
        *i += j;
    return(new);

}

int get_redir_type(char *input)
{
    if (input[1] && input[0] == '>' && input[1] == '>')
        return (APPEND_OUTPUT);
    else if (input[0] == '>')
        return (OUTPUT_REDIRECT);
    else if (input[1] && input[0] == '<' && input[1] == '<')
        return (HERE_DOCUMENT);
    else
        return (INPUT_REDIRECT);
}

int get_starting_pos(char *input)
{
    int i;

    if (input[1] && input[1] == input[0])
        i = 2;
    else
        i = 1;
    i += get_white_space_size(&input[i]);
    return (i);
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
        fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0666);
    else if (redir_type == APPEND_OUTPUT)
        fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0666);
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
        if (std_fd < 0)
            return (0);
    }
    else
    {    
        std_fd = dup2(fd, STDIN_FILENO);
        close(fd);
        if (std_fd < 0)
            return (0);
    }
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

}



int close_redirections(t_minishell *mini)
{
    dup2(mini->og_in, STDIN_FILENO);
    dup2(mini->og_out, STDOUT_FILENO);

    //if (mini->fd_out)
    //mini->fd_out = close(mini->fd_out);
      //  if (mini->fd_out == -1)
        //    return (0);
    //}
    return (1);
}


int execute_input(t_minishell *mini)
{
    char    **cmd;
    int     i;
    int     j;

    i = 0;
    j = 0;
    while (mini->input[i])
    {
        if (mini->input[i] == '|' || !mini->input[i + 1])
        {
            printf("\t I am working on a new command\t\n");
            cmd = get_cmd_value(mini->input, j, i);
            if (!cmd)
                return (errno);
            if (!check_and_handle_redirections(mini, j, i))
                return (errno);
            //handle pipe//
            // once we get cmds, we should check if they are built ins or not, and execute the functions, I'm gonna need to get the env lists for this function 
            j = i;
            
            //check cmds to decide what to execute, if built ins or excev

            char buffer[1024];
            ssize_t bytesRead;
            if (cmd[0][0] == 'c')
            {
                execve("/usr/bin/cat", cmd, NULL);
            }
            ft_printf("GOT CMDS: \n");
            for (int k = 0; cmd[k]; k++)
            {
                ft_printf("[%s]\n", cmd[k]);
            }
            if (!close_redirections(mini))
            {
                return (errno);
            }
        }
        i++;
    }

    return (0); // should return 0 if no fail, so mini shell can save the last error,
}


int main(int argc, char **argv, char **env)
{
    t_minishell mini;

    mini.input = argv[1];
    mini.fd_out = 0;
    mini.fd_in = 1;
    mini.og_out = dup(STDOUT_FILENO);
    mini.env_list = init_env(env);
    mini.err = execute_input(&mini);
    ft_printf("%s\n", argv[1]);
    close(mini.og_in);
    close(mini.og_out);
    //execute return 0 if no error and errno if error, it should be enough for minishell.er to get that value
    // built ins might want to return a different error
}