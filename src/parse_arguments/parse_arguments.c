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

int open_file(char *file_name, int redir_type)
{
    int fd;
     mode_t old_umask = umask(0);

    if (redir_type == INPUT_REDIRECT)
        fd = open(file_name, O_RDONLY);
    else if (redir_type == OUTPUT_REDIRECT)
        fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC );
    else if (redir_type == APPEND_OUTPUT)
    {
        printf("IM HERE\n");
        fd = open(file_name, O_RDWR | O_CREAT | O_APPEND );

    }
    else
        printf("Should handle logic for Here document \n");
    printf("{%i} redir_type {%s} file name\n" ,redir_type, file_name);
        umask(old_umask);  // Restore the original umask

    return (fd);
}


int execute_dup2(int fd, int redir_type)
{
    int std_fd;

    if (!fd)
        return (0);
    if (redir_type == OUTPUT_REDIRECT || redir_type == APPEND_OUTPUT)
        std_fd = dup2(fd, STDOUT_FILENO);
    else
        std_fd = dup2(fd, STDIN_FILENO);
    close(fd);
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
    fd = execute_dup2(open_file(file_name, redir_type), redir_type);
    if (fd != 0)
        return (0);
    //fd = handle_opening_file(symbol, file_name);
    
    /*
    while (input[i] && ft_isascii(input[i]) && !ft_isspace(input[i]))
    {
        printf("%c", input[i]);
        i++;
    }
    printf("\n");*/

    *start += i;
    return (fd); 
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
            printf("GOT CMDS: \n");
            for (int k = 0; cmd[k]; k++)
            {
                printf("[%s]\n", cmd[k]);
            }
        }
        i++;
    }

    return (0); // should return 0 if no fail, so mini shell can save the last error,
}


int main(int argc, char **argv, char **env)
{
    t_minishell mini;

    int fd= open("test_input", O_WRONLY | O_CREAT | O_APPEND );
    if (fd < 0)
    {perror("MiniShell");
    exit(0);}

    mini.input = argv[1];
    mini.fd_out = 0;
    mini.fd_in = 0;
    mini.env_list = init_env(env);
    mini.err = execute_input(&mini);
    if (mini.err)
        perror("MiniShell");
    printf("%s\n", argv[1]);
    //execute return 0 if no error and errno if error, it should be enough for minishell.er to get that value
    // built ins might want to return a different error
}