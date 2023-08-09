#include <libft.h>
#include <builtins.h>


t_list *get_env_node(t_list *env_list, char *str)
{
    t_list  *temp;
    char    content[100];
    int     i;

    temp = env_list;
    while (temp)
    {
        i = 0;
        while (((char *)temp->content)[i] && ((char *)temp->content)[i] != '=')
            i++;
        ft_strlcpy(content, (char *)temp->content, i + 1);
        printf("%s\n", content);
        if (ft_strcmp(content, str) == 0)
            return (temp);
        temp = temp->next;
    }
    return (NULL);
}

void print_env(t_list *env_list)
{
    t_list *temp;

    temp = env_list;
    while (temp)
    {
        printf("%s=%s\n", ((t_env *)(temp->content))->variable, \
        ((t_env *)(temp->content))->value);
        temp = temp->next;
    }
}

t_env *create_env(char *str)
{
    t_env   *new;
    char    **tab;

    new = (t_env *)malloc(sizeof(t_env));
    tab = ft_split(str, '=');
    if (!new || !tab)
        exit (1);
    new->variable = tab[0];
    new->value = tab[1];
    return (new);
}

int init_env(char **env, t_list **env_list)
{
    t_list  *tmp;
    t_list  *new;
    t_env   *env_node;
    int     i;

    env_node = create_env(env[0]);
    *(env_list) = ft_lstnew(env_node);
    if (!*env_list)
        exit(1);
    (*env_list)->last = *(env_list);
    printf("%s=%s\n", ((t_env *)((*env_list)->content))->variable, env_node->value);

    tmp = *(env_list);
    i = 1;
    while (env[i])
    {
        env_node = create_env(env[i]);
        if (!env_node)
            exit(1);
        new = ft_lstnew(env_node);
        if (!new)
            exit (1);
        tmp->next = new;
        (*env_list)->last = new;
        tmp = new;
        i++; 
    }
    return 0;
}
