#include <builtins.h>

t_list *get_env_before(t_list *env_list, char *str)
{
    t_list  *temp;

    temp = env_list;
    if (ft_strcmp(((t_env *)(temp->content))->variable, str) == 0)
        return (temp);
    while (temp->next)
    {
        if (ft_strcmp(((t_env *)(temp->next->content))->variable, str) == 0)
            return (temp);
        temp = temp->next;
    }
    return (NULL);
}

t_list *ft_unset(t_list *env_list, char *str)
{
    t_list *temp;
    t_list *next;
    t_list *before;

    if (!str)
        return (0);
    temp = get_env_node(env_list, str);
    before = get_env_before(env_list, str);
    if (!temp)
        return (0);
    next = temp->next;
    if (env_list == before)
    {
        next->last = env_list->last;
        env_list = next;
    }
    free(((t_env *)(temp->content))->value);
    free(((t_env *)(temp->content))->variable);
    free(((t_env *)(temp->content)));
    free(temp);
    if (next)
        before->next = next;
    else
    {
        before->next = NULL;
        env_list->last = before;
    }
    return (env_list);
}
