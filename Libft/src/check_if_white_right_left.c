#include "libft.h"

int check_if_white_right_left(char *argv)
{
    if (ft_isspace(argv[0]) || ft_isspace(argv[ft_strlen(argv) - 1]))
        return(1);
    return(0);
}