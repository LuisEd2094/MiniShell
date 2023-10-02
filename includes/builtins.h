#ifndef BUILTINS_H
# define BUILTINS_H
# include <libft.h>
# include <stdbool.h>


typedef struct s_env
{
    char    *variable;
    char    *value;
    bool    assigned;
} t_env;

typedef struct s_tree_node {
    t_list  * data; // Pointer to the linked list node
    struct s_tree_node* left;
    struct s_tree_node* right;
} t_tree_node;


t_tree_node	*insert_to_tbs(t_tree_node* root, t_list* value);
void		print_in_order(t_tree_node* root);

t_list		*init_env(char **env);
t_list		*get_env_node(t_list *env_list, char *str);
char		*get_env_str(char *input, t_list *env_list);
t_env		*create_env_node(char *str);
void		update_env_value(char *env_node_str, char *str);
t_list		*add_new_env(t_list *env_list, char *str);
void		free_env_list(t_list *env_list);


bool		has_equal(char *str);
void		free_tab(char **tab);

int			work_on_export(t_list *env_list, char **cmds);
t_list		*work_on_unset(t_list *env_list, char *str);

char        **ft_single_split(char const *s, char c);


/*	---	builtins	---	*/

int	ft_cd(char **arguments);
int	ft_echo(char **arguments);
void		ft_env(t_list *env_list);
int	ft_pwd(char **arguments);

#endif
