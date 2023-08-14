#ifndef INTERNAL_EXPORT_H
# define INTERNAL_EXPORT_H

# include <builtins.h>
# include <libft.h>

typedef struct s_tree_node {
    t_list  * data; // Pointer to the linked list node
    struct s_tree_node* left;
    struct s_tree_node* right;
} t_tree_node;


t_tree_node *insert_to_tbs(t_tree_node* root, t_list* value);
void        print_in_order(t_tree_node* root);


#endif