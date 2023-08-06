#include "libft.h"

void    remove_white_space(char *argv)
{
    int i;
    int k;
    int len;

    i = 0;
    if (ft_isspace(argv[i]))
    {
        while (ft_isspace(argv[i]))
            i++;
        k = 0;
        while (argv[i])
            argv[k++] = argv[i++];
        while (argv[k])
            argv[k++] = '\0';
    }
    len = ft_strlen(argv) - 1;
    if (ft_isspace(argv[len]))
    {
        while (ft_isspace(argv[len]))
            argv[len--] = '\0';
    }
}