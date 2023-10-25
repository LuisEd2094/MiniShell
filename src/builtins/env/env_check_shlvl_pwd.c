#include "env_internal.h"

void	*check_pwd(t_list *env_list)
{
	t_list	*list_node;
	char	*pwd;
	void	*return_val;

	list_node = get_env_node(env_list, "PWD");
	if (!list_node)
	{
		pwd = getcwd(NULL, 0);
		return_val = create_or_update_env_node(env_list, "PWD", pwd);
		free(pwd);
		return (return_val);
	}
	return ((void *) 1);
}

void	*check_shlvl(t_list	*env_list)
{
	t_list	*list_node;
	t_env	*env_node;
	int		level;

	list_node = get_env_node(env_list, "SHLVL");
	if (!list_node)
		return (create_or_update_env_node(env_list, "SHLVL", "1"));
	else
	{
		env_node = ((t_env *)(list_node->content));
		level = ft_atoi(env_node->value);
		free(env_node->value);
		level++;
		level = check_level(level);
		env_node->value = ft_itoa(level);
		if (!env_node->value)
			return (NULL);
	}
	return ((void *) 1);
}
