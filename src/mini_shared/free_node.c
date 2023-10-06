
#include <minishell.h>

void	free_node(t_list *temp)
{
	free(((t_env *)(temp->content))->value);
	free(((t_env *)(temp->content))->variable);
	free(((temp->content)));
	free(temp);
}