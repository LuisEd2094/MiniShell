/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:49:00 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 10:49:01 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <shared.h>

static void	free_tbs(t_tree_node *root)
{
	t_tree_node	*temp;

	if (root != NULL)
	{
		free_tbs(root->left);
		temp = root->right;
		free(root);
		free_tbs(temp);
	}
}

static void	work_on_print(t_list *env_list)
{
	t_list		*temp;
	t_tree_node	*root;

	temp = env_list;
	root = NULL;
	while (temp)
	{
		root = insert_to_tbs(root, temp);
		temp = temp->next;
	}
	print_in_order(root);
	free_tbs(root);
}

int	ft_export(t_list *env_list, char **cmds)
{
	int	i;

	i = 1;
	if (!cmds[i])
		work_on_print(env_list);
	else
	{
		while (cmds[i])
		{
			create_or_update_env_node(env_list, cmds[i]);
			i++;
		}
	}
}
