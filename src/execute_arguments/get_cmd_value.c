#include "execute_internal.h"

char *get_quoted_arg(char *input, int *start)
{
    char quote;
    char *new;
    int i;
    int j;

    i = 0;
    quote = input[i];
    if (quote == '\"')
        printf("I have to handle double quote\n");
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

char *get_new_str(int i, int j, t_minishell *mini, int *start)
{
    char *new;

    i += get_ascii_size(&mini->input[i]);
    *start = i;
    if (mini->input[j] == '$' && ft_isalnum(mini->input[j + 1]))
        return (get_env_str(&mini->input[j + 1], mini->env_list));
    new = (char *)malloc(sizeof(char) * i - j + 1);
    if (!new)
        return(NULL);
    ft_strlcpy(new, &mini->input[j], i - j + 1);
    return (new);
}

char *get_cmd_argument(t_minishell *mini, int *start, int end)
{
    int     i;
    int     j;

    i = *start;
    add_size_of_pipe(&mini->input[i], &i);
    while (mini->input[i] && i <= end)
    {
        i+= get_white_space_size(&mini->input[i]);
        if (mini->input[i] == '>' || mini->input[i] == '<')
        {
            i += get_file_redirection_size(&mini->input[i]);
            continue;
        }
        if (mini->input[i] == '|')
        {
            i++;
            continue; 
        }
        break;
    }
    if (mini->input[i] == '"' || mini->input[i] == '\'')
        return(get_quoted_arg(&mini->input[i], start));
    j = i;
    return (get_new_str(i, j, mini, start));
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

char **get_cmd_value(t_minishell *mini, int start, int end)
{
    char    **new_cmd;
    int     cmd_count;
    int     i;
    int     j;

    cmd_count = get_cmd_count(mini->input, start, end);
    new_cmd = (char **)malloc(sizeof(char *) * cmd_count + 1);
    if (!new_cmd)
        return(NULL);
    i = 0;
    j = 0;
    while(i < cmd_count)
    {
        new_cmd[j] = get_cmd_argument(mini, &start, end);
        if (!new_cmd[j])
            return (NULL);
        i++;
        if (!new_cmd[j][0])
            continue;
        j++;
    }
    while (j <= cmd_count)
        new_cmd[j++] = NULL;
    return (new_cmd);
}