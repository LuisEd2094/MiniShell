/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bts_for_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:48:46 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 10:48:47 by lsoto-do         ###   ########.fr       */
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


t_tree_node	*insert_to_tbs(t_tree_node *root, t_list *value)
{
	int			compare_result;
	t_tree_node	*new_node;

	if (!root)
	{
		new_node =(t_tree_node *)malloc(sizeof(t_tree_node));
		if (!new_node)
			return (NULL);
		new_node->data = value;
		new_node->left = NULL;
		new_node->right = NULL;
		return (new_node);
	}
	compare_result = ft_strncmp(((t_env *)(value->content))->variable, \
	((t_env *)(root->data->content))->variable, \
	ft_strlen(((t_env *)(root->data->content))->variable) + 1);
	if (compare_result < 0)
	{
		root->left = insert_to_tbs(root->left, value);
		if (!root->left)
			return (root);
	}
	else if (compare_result > 0)
	{
		root->right = insert_to_tbs(root->right, value);
		if	(!root->right)
			return(root);
	}
	return (root);
}

void	print_in_order(t_tree_node *root)
{
	if (root != NULL)
	{
		print_in_order(root->left);
		printf("declare -x %s=%c%s%c\n", \
				((t_env *)(root->data->content))->variable, \
				'"', \
				((t_env *)(root->data->content))->value, \
				'"');
		print_in_order(root->right);
	}
}
/*
t_tree_node	*init_tbs_env(t_list *env_list)
{
	t_tree_node	*root;
	t_list		*temp;

	root = NULL;
	temp = env_list;
	while (temp)
	{
		root = insert_to_tbs(root, temp);
		if (!root)
			return (NULL);
		temp = temp->next;
	}
	return (root);
}*/
