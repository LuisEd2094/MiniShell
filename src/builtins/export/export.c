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

static int print_error_export(char *cmd)
{
	print_error("minishell: export: '", 1);
	print_error(cmd, 1);
	return (print_error("': not a valid identifier\n", 1));
}

int	work_cmds_export(t_list *env_list, char **cmds)
{
	int i;
	char	**tab;
	int error;

	i = 1;
	error = 0;
	while (cmds[i])
	{
		if (cmds[i][0] == '=' || cmds[i][0] == '+')
		{
			error = print_error_export(cmds[i]);
			i++;
			continue;
		}
		tab = ft_single_split(cmds[i], '=');
		if (!tab)
			error = errno;
		else if(!create_or_update_env_node(env_list, tab[0], tab[1]))
			error = errno;
		free(tab[0]);
		free(tab[1]);
		if (tab)
			free(tab);
		i++;
	}
	return (error);
}

int	ft_export(t_list *env_list, char **cmds)
{
	char **tab;

	if (!cmds[1])
	{
		if (!work_on_print(env_list))
			return (errno);
	}
	return (work_cmds_export(env_list, cmds));
}
