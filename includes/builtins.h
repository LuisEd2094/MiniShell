#ifndef BUILTINS_H
# define BUILTINS_H
# include "./libft.h"
#include <stdbool.h>


typedef struct s_env
{
    char    *variable;
    char    *value;
    bool    assigned;
} t_env;

t_list  *init_env(char **env);
t_list  *get_env_node(t_list *env_list, char *str);
t_env   *create_env_node(char *str);
void    update_env_value(char *env_node_str, char *str);
void    add_new_env(t_list *env_list, char *str);


bool    has_equal(char *str);
void    free_tab(char **tab);

int     work_on_export(t_list *env_list, char *str);
void    print_all_env(t_list *env_list);
t_list *     work_on_unset(t_list *env_list, char *str);

char    **ft_single_split(char const *s, char c);




#endif