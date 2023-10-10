
#include <minishell.h>

void	free_env_node(t_env *env_node)
{
	if (!env_node)
		return;
	free(env_node->value);
	free(env_node->variable);
	free(env_node);
}

void	free_node(t_list *temp)
{
	free_env_node(temp->content);
	free(temp);
}