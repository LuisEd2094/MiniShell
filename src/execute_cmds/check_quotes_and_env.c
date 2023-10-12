#include "execute_cmds_internal.h"

char *remove_single_quote(char *str)
{
    int i;
    int j;

    i = 0;
    j = 1;
    while (str[j])
    {
        str[i] = str[j];
        i++;
        j++;
    }
    str[j - 1] = '\0';
    str[j - 2] = '\0'; 
    return (str);
}

char    *replace_exit_code(t_minishell *mini, char *cmd)
{
    char    *exit_code;
    char    *temp;

    exit_code = get_env_str_from_quote("?", mini->env_list);
    temp = cmd;
    cmd = ft_replace(cmd, exit_code, 0, 0);
    free(temp);
    free(exit_code);
    return (cmd);
}

char    *replace_values(char *cmd, t_minishell *mini)
{
    char    *exit_code;
    char    *temp;

    if (cmd[0] == '"')
        cmd = get_double_quote(&cmd[1], mini->env_list);
    else if (cmd[0] == '\'')
        cmd = remove_single_quote(cmd);
    else if (cmd[0] == '$' && cmd[1] == '?')
        cmd = replace_exit_code(mini, cmd);
    else if (cmd[0] == '$' && \
    is_ascii_no_space(cmd[1]) && \
    cmd[1])
        cmd = replace_env(cmd, mini->env_list , 0);
    if (!cmd)
        return (NULL);
    return (cmd);
}

void    ft_redirections(char **cmd, t_minishell *mini, int i)
{
    int j; 
    
    cmd[i + 1] = replace_values(cmd[i + 1], mini);
    check_and_handle_redirections(cmd[i], cmd[i + 1], mini);
    free(cmd[i]);
    free(cmd[i + 1]);
    j = i + 2;
    while (cmd[j])
    {
        cmd[i] = cmd[j];
        i++;
        j++;
    }
    cmd[j - 1] = NULL;
    cmd[j - 2] = NULL;
}

int check_quotes_and_env(char **cmd, t_minishell *mini)
{
    int i;
    int j;

    i = 0;
    while(cmd[i])
    {
        if (cmd[i][0] == '>' || cmd[i][0] == '<')
        {
            ft_redirections(cmd, mini, i);
            i--;
        }
        else
            cmd[i] = replace_values(cmd[i], mini);
        i++;
    }
}