#ifndef PARSE_INTERNAL_H
# define PARSE_INTERNAL_H
# include <errno.h>
# include <libft.h>
typedef enum s_redir_type
{
    INPUT_REDIRECT = 1,
    HERE_DOCUMENT,
    OUTPUT_REDIRECT,
    APPEND_OUTPUT,

} t_redir_type;


char    **get_cmd_value(char *input, int start, int end);
int     get_quotes_size(char *input);
int     get_white_space_size(char *input);
int     get_ascii_size(char *input);
int     get_file_redirection_size(char *input);
int     add_size_of_pipe(char *input, int * i);


#endif