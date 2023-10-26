/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 10:49:00 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 12:08:09 by lsoto-do         ###   ########.fr       */
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

static void	*work_on_print(t_list *env_list)
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
	return ((void *) 1);
}

void	verify_if_equal(t_list *env_list, char *variable, char *cmd)
{
	t_list	*temp;
	t_env	*env_node;

	if (has_equal(cmd))
	{
		temp = get_env_node(env_list, variable);
		if (temp)
		{
			env_node = temp->content;
			env_node->assigned = 1;
		}
	}
}

int	work_cmds_export(t_list *env_list, char **cmds)
{
	int		i;
	char	**tab;
	int		error;

	i = 1;
	error = 0;
	while (cmds[i])
	{
		tab = ft_single_split(cmds[i], '=');
		if (!tab)
			error = errno;
		if (check_valid_identifier(tab[0], EXPORT) != 0)
			error = print_invalid_identifier("export: `", cmds[i]);
		else if (!create_or_update_env_node(env_list, tab[0], tab[1]))
			error = errno;
		if (tab[0] && tab[0][0])
			verify_if_equal(env_list, tab[0], cmds[i]);
		free_2d_array(tab);
		i++;
	}
	return (error);
}

int	ft_export(t_list *env_list, char **cmds)
{
	prep_unset_export_commands(cmds);
	if (!cmds[1])
	{
		if (!work_on_print(env_list))
			return (errno);
	}
	return (work_cmds_export(env_list, cmds));
}
