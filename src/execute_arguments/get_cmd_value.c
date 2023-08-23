#include "execute_internal.h"

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
        i++;
    new = (char *)malloc(sizeof(char) * i - j + 1);
    if (!new)
        return(NULL);
    ft_strlcpy(new, &input[j], i - j + 1);
    i++;
    *start = i;
    return (new);
}

char *get_new_str(int i, int j, char *input, int *start)
{
    char *new;

    i += get_ascii_size(&input[i]);
    new = (char *)malloc(sizeof(char) * i - j + 1);
    if (!new)
        return(NULL);
    ft_strlcpy(new, &input[j], i - j +1);
    *start = i;
    return (new);
}

char *get_cmd_argument(char *input, int *start, int end)
{
    int     i;
    int     j;

    i = *start;
    add_size_of_pipe(&input[i], &i);
    while (input[i] && i <= end)
    {
        i+= get_white_space_size(&input[i]);
        if (input[i] == '>' || input[i] == '<')
        {
            i += get_file_redirection_size(&input[i]);
            continue;
        }
        if (input[i] == '|')
        {
            i++;
            continue; 
        }
        break;
    }
    if (input[i] == '"' || input[i] == '\'')
        return(get_quoted_arg(&input[i], start));
    j = i;
    return (get_new_str(i, j, input, start));
}

int get_cmd_count(char *input, int start, int end)
{
    int cmd_count;
    
    cmd_count = 0;
    add_size_of_pipe(&input[start], &start);
    while (input[start] && start <= end)
    {
        start += get_white_space_size(&input[start]);
        if (input[start] == '>' || input[start] == '<')
        {
            start += get_file_redirection_size(&input[start]);
            continue;
        }
        if (add_size_of_pipe(&input[start], &start))
            continue;
        if (input[start] == '"' || input[start] == '\'')
        {
            start += get_quotes_size(&input[start]);
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