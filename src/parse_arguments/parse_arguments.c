#include <parse_arguments.h>
#include "parse_internal.h"

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

void    skip_redirection(char *input, int *start)
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
    *start += i;   
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
            skip_redirection(&input[i], &i);
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
            char quote = input[i];
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


char   *get_file_name(char * input, int *i)
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

int    handle_redirection(char *input, int *start)
{
    char    *file_name;
    int     fd;
    int     i;
    int     redir_type;

    i = get_starting_pos(input);
    redir_type = get_redir_type(input);
    file_name = get_file_name(&input[i], &i);
    if (!file_name)
        return(0);
    //fd = handle_opening_file(symbol, file_name);
    
    /*
    while (input[i] && ft_isascii(input[i]) && !ft_isspace(input[i]))
    {
        printf("%c", input[i]);
        i++;
    }
    printf("\n");*/

    *start += i;
    return (1); 
}

void    handle_quotes(char *input, int *start)
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
    *start += i;
}

int get_cmd_count_and_handle_redirections(char *input, int start, int end, int *og_count)

{
    int cmd_count;
    
    cmd_count = 0;
    if (input [start] == '|')
    {
        //should start STDIN PIPE
        start++;
    }
    while (input[start] && start <= end)
    {
        start += get_white_space_size(&input[start]);
        if (input[start] == '>' || input[start] == '<')
        {
            if (!handle_redirection(&input[start], &start))
                return (0);
            continue;
        }
        if (input[start] == '|')
        {
            start++;
            continue; 
        }
        if (input[start] == '"' || input[start] == '\'')
        {
            handle_quotes(&input[start], &start);
            cmd_count++;
            continue;
        }
        while (input[start] && ft_isascii(input[start]) && !ft_isspace(input[start]))
            start++;   
        cmd_count++;
    }
    *og_count = cmd_count;
    return (1);
}


char **get_cmd_value_and_prep(char *input, int start, int end)
{
    char    **new_cmd;
    int     cmd_count;
    int     i;


    if (!get_cmd_count_and_handle_redirections(input, start, end, &cmd_count))
        return (NULL);
    new_cmd = (char **)malloc(sizeof(char *) * cmd_count + 1);
    if (!new_cmd)
        return(NULL);
    i = 0;
    while(i < cmd_count)
    {
        new_cmd[i] = get_cmd_argument(input, &start, end);
        if (!new_cmd[i])
        {
            return (NULL);
        }
        i++;
    }
    new_cmd[i] = NULL;
    return (new_cmd);
}


int execute_input(char *input)
{
    char            **cmd;
    int     i;
    int     j;

    i = 0;
    j = 0;
    while (input[i])
    {
        if (input[i] == '|' || !input[i + 1])
        {
            cmd = get_cmd_value_and_prep(input, j, i);
            if (!cmd)
            {
                return (errno);
            }
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
    printf("%s\n", input);
    return (0); // should return 0 if no fail, so mini shell can save the last error,
}


int main(int argc, char **argv)
{
    execute_input(argv[1]);
    //execute return 0 if no error and errno if error, it should be enough for minishell.er to get that value
    // built ins might want to return a different error
}