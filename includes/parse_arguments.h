#ifndef PARSE_ARGUMENTS_H
# define PARSE_ARGUMENT_H
# include <stdbool.h>
# include <libft.h>

typedef struct s_cmd_values
{
    char    **cmd_line;
    bool    *cmd_has_env_value; //keep track of cmd_lines that have a $ to replace later
    bool    got_pipe;
    bool    give_pipe;
    bool    logical_and; // &&
    bool    logical_or; // ||
    bool    input_redir; // <
    bool    here_document; // <<
    char    **input_info; // it looks like you can chain "<<" so cat << EOF << EOF1 wil give you the prompt until EOF and then again until EOF1, but the content in EOF seems to be ignored
    bool    output_redir; // >
    bool    append_output_redir; // >>
    char    **output_info; //need to keep a list of all files and their respective mode, as bash tries to open them even if there are multiple files to be opened, so if a file has no permision to open even if it's the last, bash will throw an error
}   t_cmd_values;

t_list *get_cmd_list(char *input);

#endif