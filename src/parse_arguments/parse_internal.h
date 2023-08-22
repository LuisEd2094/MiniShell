#ifndef PARSE_INTERNAL_H
# define PARSE_INTERNAL_H
# include <errno.h>
typedef enum s_redir_type
{
    INPUT_REDIRECT = 1,
    HERE_DOCUMENT,
    OUTPUT_REDIRECT,
    APPEND_OUTPUT,

} t_redir_type;

#endif