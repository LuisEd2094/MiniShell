#include "execute_internal.h"

int get_argument_count(char *cmd)
{
    int i;
    int arg_count;

    i = 0;
    arg_count = 0;
    while (cmd[i])
    {
        if (cmd [i] == '\"' || cmd[i] == '\'' || \
            cmd[i] == '>' || cmd[i] == '<' || \
            is_ascii_no_space(cmd[i]))
        {
            if(cmd [i] == '\"' || cmd[i] == '\'')
                i +=  get_quotes_size(&cmd[i]);
            else if (cmd[i] == '>' || cmd[i] == '<')
                i += get_redirection_size(&cmd[i]);
            else if(is_ascii_no_space(cmd[i]))
                i += get_arg_size_skip_redirections(&cmd[i]);
            arg_count++;
        }
        else
            i++;            
    }
    return (arg_count);
}


char *ft_get_arg(char *cmd, int arg_start, t_list *env_list)
{
    int arg_len;

    if (cmd[arg_start] == '<' || cmd[arg_start] == '>')
        arg_len = get_redirection_size(&cmd[arg_start]);
    else
        arg_len = get_argument_len(&cmd[arg_start]);
    if (cmd[arg_start] == '\'')
        return (ft_substr(cmd, arg_start + 1, arg_len));
    else
        return (ft_substr(cmd, arg_start, arg_len));
}

char **ft_argument_split(char *cmd, t_list *env_list)
{
    char    **args;
    int     arg_count;
    int     i;
    int     arg_start;

    arg_count = get_argument_count(cmd);
    args = (char **)malloc(sizeof(char *) * (arg_count + 1));
    if (!args)
        exit (1);
    i = 0;
    arg_start = 0;
    while (i < arg_count)
    {
        arg_start += get_white_space_size(&cmd[arg_start]);
        if (cmd[arg_start] == '"')
            args[i] = get_double_quote(&cmd[arg_start + 1], env_list);
        else
            args[i] = ft_get_arg(cmd, arg_start, env_list);
        if (!args[i])
            exit (1); //handle malloc
        arg_start += move_start(&cmd[arg_start]);
        i++;
    }
    args[i] = NULL;
    return (args);
}



char **get_cmd_argument(char *cmd, t_list *env)
{
    char    **cmd_arguments;
    int     i;
    int     j;

    cmd_arguments = ft_argument_split(cmd, env);
    if (!cmd_arguments)
        return (NULL);
    i = 0;
    while (cmd_arguments[i])
    {
        j = 0;
        while (cmd_arguments[i][j] )
        {
            if (cmd_arguments[i][j] == '$' && \
            is_ascii_no_space(cmd_arguments[i][j + 1]) && \
            cmd_arguments[i][j + 1])
                cmd_arguments[i] = replace_env(cmd_arguments[i], env , j);
            if (!cmd_arguments[i])
                exit(1);
            j++;
        }
        i++;
    }
    return (cmd_arguments);
}