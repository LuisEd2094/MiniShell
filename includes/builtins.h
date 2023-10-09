#ifndef BUILTINS_H
# define BUILTINS_H
# include <libft.h>
# include <stdbool.h>
# include <errno.h>

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
t_env       *create_env_node(char *variable, char *value);
t_list		*add_new_env(t_list *env_list, char *variable, char *value);
void		free_env_list(t_list *env_list);


bool		has_equal(char *str);
void		free_tab(char **tab);

char        **ft_single_split(char const *s, char c);


/*	---	builtins	---	*/

int	ft_cd(char **arguments, t_list *env_list);
int	ft_echo(char **arguments);
int	ft_print_env(char **cmds, t_list *env_list);
int	ft_export(t_list *env_list, char **cmds);
int	ft_pwd(char **arguments);


#endif
