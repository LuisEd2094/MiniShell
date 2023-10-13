/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bts_for_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:48:46 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 12:03:05 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <builtins.h>
#include <shared.h>

t_tree_node	*create_node(t_list *value)
{
	t_tree_node	*new_node;

	new_node = (t_tree_node *)malloc(sizeof(t_tree_node));
	if (!new_node)
		return (NULL);
	new_node->data = value;
	new_node->left = NULL;
	new_node->right = NULL;
	return (new_node);
}

t_tree_node	*insert_to_tbs(t_tree_node *root, t_list *value)
{
	int	compare_result;

	if (!root)
		return(create_node(value));
	compare_result = ft_strcmp(((t_env *)(value->content))->variable, \
	((t_env *)(root->data->content))->variable);
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
	t_env *node;

	node = NULL;
	if (root != NULL)
	{
		print_in_order(root->left);
		node = ((t_env *)(root->data->content));
		if (ft_strcmp(node->variable, "?") != 0 &&
		node->assigned)
		ft_printf("declare -x %s=%c%s%c\n", \
				node->variable, \
				'"', \
				node->value, \
				'"');
		else if (!node->assigned)
		{
			ft_printf("declare -x %s\n", \
				node->variable);

		}
		print_in_order(root->right);
	}
}
