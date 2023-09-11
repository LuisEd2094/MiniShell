#include <builtins.h>

t_list *get_env_node(t_list *env_list, char *str)
{
    t_list  *temp;

    temp = env_list;
    while (temp)
    {
        if (ft_strcmp(((t_env *)(temp->content))->variable, str) == 0)
            return (temp);
        temp = temp->next;
    }
    return (NULL);
}

bool has_equal(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (str[i] == '=')
            return (1);
        i++;
    }
    return (0);
}

t_env *create_env_node(char *str)
{
    t_env   *new;
    char    **tab;

    new = (t_env *)malloc(sizeof(t_env));
    tab = ft_single_split(str, '=');
    if (!new || !tab)
        exit (1);
    new->variable = tab[0];
    new->value = tab[1];
    if (has_equal(str))
        new->assigned = 1;
    else
        new->assigned = 0;
    free(tab);
    return (new);
}

t_list *    add_new_env(t_list *env_list, char *str)
{
    t_list  *temp;
    t_list  *new;
    t_env   *env_node;

    temp = env_list->last;
    env_node = create_env_node(str);
    new = ft_lstnew(env_node);
    temp->next = new;
    env_list->last = new;
    return (new); 
}

void    update_env_value(char *env_node_str, char *str)
{
    int     i;
    char    *new;

    free(env_node_str);
    ft_strlcpy(env_node_str, str, ft_strlen(str));
    
    i = ft_strlen(str);
    new = (char *)malloc(sizeof(char) * i  + 1);
    if (!new)
        exit(0);
    i = -1;
    while(str[++i])
        new[i] = str[i];
    new[i] = '\0';
    env_node_str = new;
}