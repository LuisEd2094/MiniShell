#include "execute_internal.h"

int get_argument_count(char *cmd)
{
    int i;
    int arg_count;

    i = 0;
    arg_count = 0;
    while (cmd[i])
    {
        if(cmd [i] == '\"' || cmd[i] == '\'')
        {
            i +=  get_quotes_size(&cmd[i]);
            arg_count++;
            continue;
        }
        else if (cmd[i] == '>' || cmd[i] == '<')
        {
            i += get_redirection_size(&cmd[i]);
            arg_count++;
            continue;
        }
        else if(ft_isascii(cmd[i]) && !ft_isspace(cmd[i]))
        {
            i += get_arg_size_skip_redirections(&cmd[i]);
            arg_count++;
            continue;
        }
        i++;            
    }
    return (arg_count);
}

int get_argument_len(char *cmd)
{
    int i; 

    i = 0;
    if (cmd[i] == '\'' || cmd[i] == '"')
    {
        i = get_quotes_size(cmd);
        i -= 2;
    } 
    else
        i = get_arg_size_skip_redirections(cmd);
    return (i);

}

int skip_quote(char c)
{
    if (c == '\'' || c == '\"')
        return (1);
    return (0);
}


int get_env_name_len(char *cmd)
{
    int len;

    len = 0;
    while (cmd[len] && cmd[len] != '"' && !ft_isspace(cmd[len]) \
        && cmd[len] != '<' && cmd[len] != '>')
        len++;
    return (len);
}


char *get_env_name(char *cmd)
{
    int len;

    len = get_env_name_len(cmd);
    return (ft_substr(cmd, 0, len));
}

char *get_env_str_from_quote(char *cmd, t_list *env_list)
{
    char    *env_name;
    char    *to_return;
    int len;

    len = 0;
    env_name = get_env_name(cmd);
    if (!env_name)
        return (NULL);
    to_return = get_env_str(env_name, env_list);
    free(env_name);
    return (to_return);
}


char *ft_replace(char *cmd, char *env, int i)
{
    static  bool done_replace = 0; 
    char    *str_first_half;
    char    *str_second_half;
    char    *new;
    int     j;

    if (i > 0);
        str_first_half = ft_substr(cmd, 0, i);
    j = 0;
    while (cmd[j] && cmd[j] != '$')
        j++;
    j++;
    j += get_env_name_len(&cmd[j]);
    str_second_half = ft_substr(cmd, j, ft_strlen(cmd));
    new = (char *)malloc(sizeof(char) * (ft_strlen(str_first_half) + ft_strlen(str_second_half) + ft_strlen(env)) + 1);
    ft_strlcpy(new, str_first_half, ft_strlen(str_first_half) + 1);
    ft_strlcat(new, env, ft_strlen(env) + ft_strlen(new) + 1);
    ft_strlcat(new, str_second_half, ft_strlen(str_second_half) + ft_strlen(new));
    free(str_first_half);
    free(str_second_half);    
    return (new);
}

char *get_double_quote(char *cmd, t_list *env_list)
{
    char    *new;
    char    *temp;
    char    *env;
    int     i;
    int     j; 
    
    i = 0;
    j = 0;
    
    while (cmd[i] && cmd[i] != '"')
    {
        if (cmd[i] == '$')
        {
            env = get_env_str_from_quote(&cmd[i + 1], env_list);
            new = ft_replace(cmd, env, i);
        }
        i++;
    }
    return (new);
}

int move_start(char *cmd)
{
    int i;

    i = 0;
    if (cmd[i] == '<' || cmd[i] == '>')
        return (get_redirection_size(&cmd[i]));
    else
        return (get_argument_len(&cmd[i]));
}
char **ft_argument_split(char *cmd, t_list *env_list)
{
    char    **args;
    int     arg_count;
    int     i;
    int     arg_start;
    int     arg_len;

    arg_count = get_argument_count(cmd);
    args = (char **)malloc(sizeof(char *) * arg_count + 1);
    if (!args)
        exit (1);
    i = 0;
    arg_start = 0;
    while (i < arg_count)
    {
        arg_start += get_white_space_size(&cmd[arg_start]);

        //arg_start += skip_quote(cmd[arg_start]);
        if (cmd[arg_start] == '"')
            args[i] = get_double_quote(&cmd[arg_start + 1], env_list);
        else
        {
            if (cmd[arg_start] == '<' || cmd[arg_start] == '>')
                arg_len = get_redirection_size(&cmd[arg_start]);
            else
                arg_len = get_argument_len(&cmd[arg_start]);
            if (cmd[arg_start] == '\'')
                args[i] = ft_substr(cmd, arg_start + 1, arg_len);
            else
                args[i] = ft_substr(cmd, arg_start, arg_len);
        }
        arg_start += move_start(&cmd[arg_start]);
        i++;
    }
    return (args);
}



char *replace_env(char *cmd, t_list *env)
{
    char *temp;

    temp = get_env_str(&cmd[1], env);
    if (!temp)
        return (NULL);
    free(cmd);
    return (temp);
}

char **get_cmd_argument(char *cmd, t_list *env)
{
    char    **cmd_arguments;
    int     i;

    cmd_arguments = ft_argument_split(cmd, env);
    if (!cmd_arguments)
        return (NULL);
    i = 0;
    while (cmd_arguments[i])
    {
        if (cmd_arguments[i][0] == '$')
        {
            cmd_arguments[i] = replace_env(cmd_arguments[i], env);
            if (!cmd_arguments[i])
                exit(1);
        }
        i++;
    }
    return (cmd_arguments);
}

int get_cmd_count(char **cmds)
{
    int cmd_count;

    cmd_count = 0;
    while(cmds[cmd_count])
        cmd_count++;
    return (cmd_count);
}

char ***get_cmds_value(char * input, t_list *env)
{
    char    ***triple_cmds;
    char    **double_cmds;
    int     cmd_count;
    int     i;

    double_cmds = ft_split(input, '|');
    if (!double_cmds)
        exit (1);
    cmd_count = get_cmd_count(double_cmds);
    triple_cmds = (char ***)malloc(sizeof(char **) * cmd_count + 1);
    if (!triple_cmds)
        exit (1);
    i = 0;
    while (i < cmd_count)
    {
        triple_cmds[i] = get_cmd_argument(double_cmds[i], env);
        if (!triple_cmds[i])
            exit (1); //need to handle frees;
        i++;
    }
    triple_cmds[i] = NULL;
    return  (triple_cmds);
}
