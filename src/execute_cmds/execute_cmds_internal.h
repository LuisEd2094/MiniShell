#ifndef EXECUTE_CMDS_INTERNAL_H
# define EXECUTE_CMDS_INTERNAL_H  

# include <errno.h>
# include <libft.h>
# include <minishell.h>
# include <shared.h>


char	*replace_env(char *cmd, t_list *env_list, int j);
char	*ft_replace(char *cmd, char *env, int i, bool found);

char	*get_env_str_from_quote(char *cmd, t_list *env_list);

char	*get_next_word(char *cmd);
int		get_next_word_len(char *cmd);
char    **ft_commands_split(char *input);



///
char	*get_double_quote(char *cmd, t_list *env_list);



#endif