#include <libft.h>

int ft_exit(char **cmd)
{
    exit(ft_atoi(cmd[1]));
}