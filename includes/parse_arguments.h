#ifndef PARSE_ARGUMENTS_H
# define PARSE_ARGUMENT_H
# include <stdbool.h>
# include <libft.h>

typedef struct s_arguments
{
    char    **cmd_line;
    bool    got_pipe;
    bool    give_pipe;
    bool    logical_and; // &&
    bool    logical_or; // ||
    bool    input_redir; // <
    bool    here_document; // <<
    char    *input_info;
    bool    output_redir; // >
    bool    append_output_redir; // >>
    char    **output_info;
}   t_arguments;

t_list *get_cmd_list(char *input);

#endif