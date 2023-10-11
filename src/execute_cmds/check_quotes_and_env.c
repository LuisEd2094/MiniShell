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

char    *replace_values(char *cmd, t_minishell *mini)
{
    if (cmd[0] == '"')
        cmd = get_double_quote(&cmd[1], mini->env_list);
    else if (cmd[0] == '\'')
        cmd = remove_single_quote(cmd);
    else if (cmd[0] == '$' && cmd[1] == '?')
        cmd = ft_itoa(mini->exit_code);
    else if (cmd[0] == '$' && \
    is_ascii_no_space(cmd[1]) && \
    cmd[1])
        cmd = replace_env(cmd, mini->env_list , 0);
    if (!cmd)
        return (NULL);
    return (cmd);
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
            printf("I am redirection\n");
            check_and_handle_redirections(cmd[i], replace_values(cmd[i + 1], mini), mini);
            free(cmd[i]);
            free(cmd[i + 1]);
            j = i + 2;
            int temp = i;
            while (cmd[j])
            {
                cmd[i] = cmd[j];
                i++;
                j++;
            }
            cmd[j - 1] = NULL;
            cmd[j - 2] = NULL;
            i = temp - 1;


        }
        else
        {
            printf("[%s] I am not redirectio\n", cmd[i]);
            cmd[i] = replace_values(cmd[i], mini);
        }
        /*
        if (cmd[i][j] == '"')
            cmd[i] = get_double_quote(&cmd[i][j + 1], mini->env_list);
        else if (cmd[i][j] == '\'')
            cmd[i] = remove_single_quote(cmd[i]);
        else if (cmd[i][j] == '$' && cmd[i][j + 1] == '?')
            cmd[i] = ft_itoa(mini->exit_code);
        else if (cmd[i][j] == '$' && \
        is_ascii_no_space(cmd[i][j + 1]) && \
        cmd[i][j + 1])
            cmd[i] = replace_env(cmd[i], mini->env_list , j);
        if (!cmd[i])
            exit(1);*/
        i++;
    }
}