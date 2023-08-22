#include <minishell.h>
#include "parse_internal.h"

int    skip_quotes(char *input)
{
    char    quote;
    int     i;
    
    i = 0;
    quote = input[i];
    i++;
    while(input[i] != quote)
    {
        i++;
    }
    //printf("\n");

    i++;
    return(i);
}

int get_white_space_size(char *input)
{
    int i;

    i = 0;
    while(input[i] && ft_isspace(input[i]))
        i++;
    return (i);
}

int get_ascii_size(char *input)
{
    int i;

    i = 0;
    while (input[i] && ft_isascii(input[i]) && !ft_isspace(input[i]))
    {
        i++;
    }
    return (i);
}

int    skip_redirection(char *input)
{
    int     i;
    char    symbol;

    i = 0;
    symbol = input[i];
    if (input[i + 1] && input[i + 1] == symbol)
        i += 2;
    else
        i++;
    i += get_white_space_size(&(input[i]));
    i += get_ascii_size(&input[i]);
    return (i); 
}


char *get_quoted_arg(char *input, int *start)
{
    char quote;
    char *new;
    int i;
    int j;

    i = 0;
    quote = input[i];
    i++;
    j = i;
    while(input[i] != quote)
    {
        //printf("%c", input[i]);
        i++;
    }
    new = (char *)malloc(sizeof(char) * i - j + 1);
    if (!new)
        return(NULL);
    ft_strlcpy(new, &input[j], i - j + 1);
    i++;
    *start = i;

    //printf(" [%i] size\n", i - 1 - j);

    return (new);
}

char *get_cmd_argument(char *input, int *start, int end)
{
    char    *new;
    int i;
    int j;

    i = *start;
    j = *start;
    if(input[i] == '|')
        i++;
    while (input[i] && i <= end)
    {
        i+= get_white_space_size(&input[i]);
        if (input[i] == '>' || input[i] == '<')
        {
            i += skip_redirection(&input[i]);
            continue;
        }
        if (input[i] == '|')
        {
            i++;
            continue; 
        }
        if (input[i] == '"' || input[i] == '\'')
        {
            return(get_quoted_arg(&input[i], start));
        }
        j = i;
        i += get_ascii_size(&input[i]);
       // printf(" [%i] size\n", i - j);
        new = (char *)malloc(sizeof(char) * i - j + 1);
        if (!new)
            return(NULL);
        ft_strlcpy(new, &input[j], i - j +1);
        *start = i;
        return (new);
    }

}


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

int print_error(char *err_description)
{
    if (err_description)
        perror(err_description);
    else
        perror(NULL);
    return (0);
}

int open_file(char *file_name, int redir_type)
{
    int fd;

    if (redir_type == INPUT_REDIRECT)
    {
        if (access(file_name, R_OK) != 0)
            return(print_error(file_name));
    }
    else if ( redir_type == OUTPUT_REDIRECT ||  redir_type == APPEND_OUTPUT)
    {
        if (access(file_name, W_OK) != 0)
            return(print_error(file_name));
    }
    if (redir_type == INPUT_REDIRECT)
        fd = open(file_name, O_RDONLY);
    else if (redir_type == OUTPUT_REDIRECT)
        fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644);
    else if (redir_type == APPEND_OUTPUT)
        fd = open(file_name, O_RDWR | O_CREAT | O_APPEND, 0644);
    else
        printf("Should handle logic for Here document \n");
    return (fd);
}


int execute_dup2(int fd, int redir_type, t_minishell *mini)
{
    int std_fd;


    if (!fd)
        return (0);
    if (redir_type == OUTPUT_REDIRECT || redir_type == APPEND_OUTPUT)
    {
        mini->fd_out = dup2(fd, STDOUT_FILENO);
        close(fd);
        if (mini->fd_out < 0)
            return (0);
    }
    else
    {    
        mini->fd_in = dup2(fd, STDIN_FILENO);
        close(fd);
        if (mini->fd_in < 0)
            return (0);
    }
    return (1);
}

int handle_redirection(t_minishell *mini, char *input, int *start)
{
    int i;
    char *file_name;
    int redir_type;
    int fd; 
    
    printf("inside handle_redirections[%s]\n", input);
    i = get_starting_pos(input);
    redir_type = get_redir_type(input);
    file_name = get_file_name(&(input[i]), &i);
    printf("FILE NAME [%s]\n", file_name);
    if (!file_name)
        return(0);
    //fd = open_file(file_name, redir_type);
    if (!execute_dup2(open_file(file_name, redir_type), redir_type, mini))
        return (0);
    //close (fd);
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
        //start += get_white_space_size(&input[start]);
        if (input[start] == '>' || input[start] == '<')
        {
            if (!handle_redirection(mini, &input[start], &start))
                return (0);
        }
        /*
        if (input[start] == '|')
        {
            start++;
            continue; 
        }
        if (input[start] == '"' || input[start] == '\'')
        {
            start += skip_quotes(&input[start]);
            continue;
        }
        start += get_ascii_size(&input[start]);*/
    }
    return(1);

}



int get_cmd_count(char *input, int start, int end)

{
    int cmd_count;
    
    cmd_count = 0;
    if (input [start] == '|')
        start++;
    while (input[start] && start <= end)
    {
        start += get_white_space_size(&input[start]);
        if (input[start] == '>' || input[start] == '<')
        {
            start += skip_redirection(&input[start]);
            continue;
        }
        if (input[start] == '|')
        {
            start++;
            continue; 
        }
        if (input[start] == '"' || input[start] == '\'')
        {
            start += skip_quotes(&input[start]);
            cmd_count++;
            continue;
        }
        start += get_ascii_size(&input[start]);
        cmd_count++;
    }
    return(cmd_count);
}


char **get_cmd_value(char *input, int start, int end)
{
    char    **new_cmd;
    int     cmd_count;
    int     i;



    cmd_count = get_cmd_count(input, start, end);
    new_cmd = (char **)malloc(sizeof(char *) * cmd_count + 1);
    if (!new_cmd)
        return(NULL);
    i = 0;
    while(i < cmd_count)
    {
        new_cmd[i] = get_cmd_argument(input, &start, end);
        if (!new_cmd[i])
            return (NULL);
        i++;
    }
    new_cmd[i] = NULL;
    return (new_cmd);
}

int close_redirections(t_minishell *mini)
{
    if (mini->fd_in == STDIN_FILENO)
    {
        if (close(mini->fd_in) == -1)
            return (0);
        mini->fd_in = 1;
    }
    if (mini->fd_out == STDOUT_FILENO)
    {
        mini->fd_out = close(mini->fd_out);
        if (mini->fd_out == -1)
            return (0);
    }
    return (1);
}


int execute_input(t_minishell *mini)
{
    char    **cmd;
    char    *input;
    int     i;
    int     j;

    i = 0;
    j = 0;
    input = mini->input;
    while (input[i])
    {
        if (input[i] == '|' || !input[i + 1])
        {
            printf("\tI am starting a new comand \n");
            cmd = get_cmd_value(input, j, i);
            if (!cmd)
            {
                return (errno);
            }
            if (!check_and_handle_redirections(mini, j, i))
                return (errno);
            //handle redirection//
            //handle pipe//
            // once we get cmds, we should check if they are built ins or not, and execute the functions, I'm gonna need to get the env lists for this function 
            j = i;
            
            char buffer[1024];
            ssize_t bytesRead;
            printf("mini->fd_in %i\n", mini->fd_in);
            if (mini->fd_in == 0)
            {
                printf("I AM PRINT\n");
                while ((bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
                // Process the data read from the file
                    write(STDOUT_FILENO, buffer, bytesRead); // Output the data to standard output
                }
            }
            printf("GOT CMDS: \n");
            for (int k = 0; cmd[k]; k++)
            {
                printf("[%s]\n", cmd[k]);
            }
            if (!close_redirections(mini))
                return (errno);
            printf("I've finished closing\n");
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
    mini.env_list = init_env(env);
    mini.err = execute_input(&mini);
    printf("%s\n", argv[1]);
    //execute return 0 if no error and errno if error, it should be enough for minishell.er to get that value
    // built ins might want to return a different error
}