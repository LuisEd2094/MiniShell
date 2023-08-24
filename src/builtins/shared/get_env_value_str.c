#include <minishell.h>

static int get_ascii_size(char *input)
{
    int i;

    i = 0;
    while (input[i] && ft_isascii(input[i]) && !ft_isspace(input[i]))
        i++;
    return (i);
}

char *get_env_str(char *input, t_list *env_list)
{
    t_list   *env_node;
    char    *env_name;
    int     env_name_len;

    env_name_len = get_ascii_size(input);
    env_name = (char *)malloc(sizeof(char) * env_name_len + 1);
    if (!env_name)
        exit(1);
    ft_strlcpy(env_name, input, env_name_len + 1);
    env_node = get_env_node(env_list, env_name);
    free(env_name);
    if (!env_node)
        return ("\0");
    env_name_len  = ft_strlen(((t_env *)env_node->content)->value);
    env_name = (char *)malloc(sizeof(char) * env_name_len + 1);
     if (!env_name)
        exit(1);
    ft_strlcpy(env_name, ((t_env *)env_node->content)->value, \
    env_name_len + 1);
    return(env_name);
}