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

static void *work_on_print(t_list *env_list)
{
	t_list		*temp;
	t_tree_node	*root;

	temp = env_list;
	root = NULL;
	if (!env_list->content)
		return ((void *) 1);
	while (temp)
	{
		root = insert_to_tbs(root, temp);
		if (errno == ENOMEM)
		{			
			free_tbs(root);
			return (print_perror());
		}
		temp = temp->next;
	}
	print_in_order(root);
	free_tbs(root);
}

int	ft_export(t_list *env_list, char **cmds)
{
	char **tab;
	int	i;

	i = 1;
	if (!cmds[i])
	{
		if (!work_on_print(env_list))
			return (errno);
	}
	else
	{
		while (cmds[i])
		{
			tab = ft_single_split(cmds[i], '=');
			if (!tab)
				exit(1);
			if(!create_or_update_env_node(env_list, tab[0], tab[1]))
				return (errno);
			free(tab);
			i++;
		}
	}
	return (0);
}
