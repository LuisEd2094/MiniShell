#include <builtins.h>
#include <shared.h>


static void free_tbs(t_tree_node *root)
{
    t_tree_node *temp;

    if (root != NULL)
    {
        free_tbs(root->left);
        temp = root->right;
        free(root);
        free_tbs(temp);       
    }

}
static void work_on_print(t_list *env_list)
{
    t_list *temp;
    t_tree_node *root;

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



int work_on_export(t_list *env_list, char *str)
{
    char **tab;
    t_list  *temp;
    t_list  *new;
    t_env   *env_node;

    tab = NULL;
    if (!str)
        work_on_print(env_list);
    else
        create_or_update_env_node(env_list, str);
    
}