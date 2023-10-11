#ifndef ENV_INTERNAL_H
# define ENV_INTERNAL_H
# include <builtins.h>
# include <shared.h>
# include <minishell.h>

t_list	*iter_env(char *env);
t_list	*fill_up_env_list(t_list *env_list, char **env);
t_list  *create_empty_list(void);
t_env	*create_new_env_node(char *env);




#endif