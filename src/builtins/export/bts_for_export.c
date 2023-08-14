#include <builtins.h>

t_tree_node *insert_to_tbs(t_tree_node* root, t_list* value)
{
    int compare_result;
    t_tree_node *new_node;

    if (ft_strcmp(((t_env *)(value->content))->variable, "_") == 0)
        return (root);
    if (!root)
    {
        new_node= (t_tree_node *)malloc(sizeof(t_tree_node));
        if (!new_node)
            exit (1);
        new_node->data = value;
        new_node->left = NULL;
        new_node->right = NULL;
        return (new_node);
    }
    compare_result = ft_strcmp(((t_env *)(value->content))->variable, \
    ((t_env *)(root->data->content))->variable);
    if (compare_result < 0)
        root->left = insert_to_tbs(root->left, value);
    else if (compare_result > 0)
        root->right = insert_to_tbs(root->right, value);
    return (root);
}


void        print_in_order(t_tree_node* root)
{
    if (root != NULL)
    {
        print_in_order(root->left);
        printf("declare -x %s=%c%s%c\n", ((t_env *)(root->data->content))->variable, '"',((t_env *)(root->data->content))->value, '"');
        print_in_order(root->right);
    }
}

t_tree_node *init_tbs_env(t_list *env_list)
{
    t_tree_node *root;
    t_list      *temp;

    root = NULL;
    temp = env_list;
    while (temp)
    {
        root = insert_to_tbs(root, temp);
        temp = temp->next;
    }
    return (root);
}
