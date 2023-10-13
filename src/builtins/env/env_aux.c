#include "env_internal.h"

t_list	*iter_env(char *env)
{
	t_list	*new;
	t_env	*env_node;

	env_node = create_new_env_node(env);
	if (!env_node)
		return (NULL);
	new = ft_lstnew(env_node);
	if (!new)
	{
		free_env_node(env_node);
		return (print_perror());
	}
	return (new);
}

t_list	*fill_up_env_list(t_list *env_list, char **env)
{
	int		i;
	t_list	*tmp;

	tmp = env_list;
	i = 1;
	while (env[i])
	{
		tmp->next = iter_env(env[i]);
		if (!tmp->next)
			break ;
		tmp = tmp->next;
		env_list->last = tmp;
		i++;
	}
	return (env_list);
}


t_list  *create_empty_list(void)
{	
    t_list	*env_list;
    env_list = ft_lstnew(NULL);
    if (!env_list)
        exit(EXIT_FAILURE);
    return (env_list);
}