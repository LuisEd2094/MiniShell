#include <builtins.h>

t_list *get_env_before(t_list *env_list, char *str)
{
    t_list  *temp;

    temp = env_list;
    while (temp->next)
    {
        if (ft_strcmp(((t_env *)(temp->next->content))->variable, str) == 0)
            return (temp);
        temp = temp->next;
    }
    return (NULL);
}

int     work_on_unset(t_list *env_list, char *str)
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
    
}
