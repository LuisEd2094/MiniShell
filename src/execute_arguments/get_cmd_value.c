#include "execute_internal.h"
/*
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
*/

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
        else if(ft_isascii(cmd[i]) && !ft_isspace(cmd[i]))
        {
            i += get_ascii_size(&cmd[i]);
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
    if (cmd[i] == '\"' || cmd[i] == '\'')
    {
        i = get_quotes_size(cmd);
        i -= 2;
    } 
    else
        i = get_ascii_size(cmd);
    return (i);

}

int skip_quote(char c)
{
    if (c == '\'' || c == '\"')
        return (1);
    return (0);
}

char **ft_argument_split(char *cmd)
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
        arg_len = get_argument_len(&cmd[arg_start]);
        arg_start += skip_quote(cmd[arg_start]);
        args[i] = ft_substr(cmd, arg_start, arg_len);
        arg_len += skip_quote(cmd[arg_len]);
        arg_start += arg_len;
        i++;
    }
    return (args);
    
}



char **get_cmd_argument(char *cmd)
{
    char    **cmd_arguments;

    cmd_arguments = ft_argument_split(cmd);
    if (!cmd_arguments)
        return (NULL);
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

char ***get_cmds_value(char * input)
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
        triple_cmds[i] = get_cmd_argument(double_cmds[i]);
        if (!triple_cmds[i])
            exit (1); //need to handle frees;
        i++;
    }
    triple_cmds[i] = NULL;
    return  (triple_cmds);
}
