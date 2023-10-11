#ifndef PARSE_INPUT_INTERNAL_H
# define PARSE_INPUT_INTERNAL_H
# include <libft.h>
# include <stdbool.h>
# include <shared.h>

#define UNEXPECTED "minishell: syntax error near unexpected token "
#define QUOTES "minishell: syntax error, unclosed quote"
#define PIPES  "minishell: syntax error, unclosed pipe"

typedef struct s_input
{
    char    quote;
    char    redir_token;
    int     redir_pos;
    bool    pipe;
    bool    left_of_pipe;
    bool    redirections;
}   t_input;

#endif


