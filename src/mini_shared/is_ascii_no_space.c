#include <libft.h>

int is_ascii_no_space(char c)
{
    if(ft_isascii(c) && !ft_isspace(c))
        return (1);
    return (0);
}