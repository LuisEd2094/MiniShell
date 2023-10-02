#include <builtins.h>

void	ft_env(t_list *env_list)
{
	t_list	*temp;

	temp = env_list;
	while (temp)
	{
		if (((t_env *)(temp->content))->assigned)
			ft_printf("%s=%s\n", ((t_env *)(temp->content))->variable, \
		((t_env *)(temp->content))->value);
		temp = temp->next;
	}
}

void	free_env_list(t_list *env_list)
{
	t_list	*cursor;
	t_list	*next;

	cursor = env_list;
	next = cursor->next;
	while (cursor)
	{
		free(((t_env *)(cursor->content))->variable);
		free(((t_env *)(cursor->content))->value);
		free((cursor->content));
		free(cursor);
		cursor = next;
		if (next)
			next = next->next;
	}
}

t_list	*init_env(char **env)
{
	t_list	*env_list;
	t_list	*tmp;
	t_list	*new;
	t_env	*env_node;
	int		i;

	env_node = create_env_node(env[0]);
	env_list = ft_lstnew(env_node);
	if (!env_list)
		exit(1);
	env_list->last = env_list;
	tmp = env_list;
	i = 1;
	while (env[i])
	{
		env_node = create_env_node(env[i]);
		if (!env_node)
			exit(1);
		new = ft_lstnew(env_node);
		if (!new)
			exit (1);
		tmp->next = new;
		env_list->last = new;
		tmp = new;
		i++;
	}
	return (env_list);
}
