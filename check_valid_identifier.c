#include <libft.h>
#include <stdbool.h>

# define EXPORT 1
# define UNSET	2


bool check_unset(char *arg)
{
    int i;

    i = -1;
    while(arg[++i])
    {
        if (ft_isdigit(arg[i]) && i == 0)
            return (1);
        else if (!ft_isalnum(arg[i]) && arg[i] != '_')
            return (1);
    }
    return (0);
}

int check_export(char *arg)
{
    return 1;
}


int check_valid_identifier(char *arg, int order)
{
    if (order == EXPORT)
        return (check_export(arg));
    else
        return (check_unset(arg));
}