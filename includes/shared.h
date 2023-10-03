#ifndef SHARED_H
# define SHARED_H

int get_next_word_len(char *cmd);
char *get_next_word(char *cmd);
int    get_quotes_size(char *input);
int get_white_space_size(char *input);
int get_arg_size_skip_redirections(char *input);

int    get_redirection_size(char *input);
int is_ascii_no_space(char c);
char *ft_replace(char *cmd, char *env, int i, bool found);
void create_or_update_env_node(t_list *env_list, char *str);
int cmd_len(char **cmd);
int print_error(char *err_description, int err_value);



#endif