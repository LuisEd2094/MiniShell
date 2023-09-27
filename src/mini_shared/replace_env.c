#include <minishell.h>

char *get_second_half(char *cmd)
{
    int j;
    int k;
    
    j = 0;
    while (cmd[j] && cmd[j] != '$')
        j++;
    j++;
    j += get_next_word_len(&cmd[j]);
    k = j;
    while (cmd[k] && cmd[k] != '"')
        k++;
    if (k == j)
       return(ft_calloc(1, sizeof(char)));
    else
        return(ft_substr(cmd, j, k));

}
char *get_first_half(char *cmd, int i)
{
    if (i > 0)
        return(ft_substr(cmd, 0, i));
    else
        return(ft_calloc(1, sizeof(char)));
}

char *ft_replace(char *cmd, char *env, int i, bool found)
{
    char    *str_first_half;
    char    *str_second_half;
    char    *new;

    str_first_half = get_first_half(cmd, i);
    str_second_half = get_second_half(cmd);
    new = (char *)malloc(sizeof(char) * (ft_strlen(str_first_half) + ft_strlen(str_second_half) + ft_strlen(env)) + 1);
    ft_strlcpy(new, str_first_half, ft_strlen(str_first_half) + 1);
    ft_strlcat(new, env, ft_strlen(env) + ft_strlen(new) + 1);
    ft_strlcat(new, str_second_half, ft_strlen(str_second_half) + ft_strlen(new) + 1);
    free(str_first_half);
    free(str_second_half);
    if (found)
        free(cmd);    
    return (new);
}


char *get_env_str_from_quote(char *cmd, t_list *env_list)
{
    char    *env_name;
    char    *to_return;
    int len;

    len = 0;
    env_name = get_next_word(cmd);
    if (!env_name)
        return (NULL);
    to_return = get_env_str(env_name, env_list);
    free(env_name);
    return (to_return);
}


char *replace_env(char *cmd, t_list *env_list, int j)
{
    char    *temp;
    char    *env;

    env = get_env_str_from_quote(&cmd[j + 1], env_list);
    temp = ft_replace(cmd, env, j, 0);
    free(env);
    if (!temp)
        return (NULL);
    free(cmd);
    return (temp);
}