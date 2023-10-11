#include <libft.h>
#include <minishell.h>

int ft_exit(char **cmd, t_minishell *mini)
{
    int i;
    int len;

    len = 0;
    while(cmd[len])
        len++;
    if (len > 2)
    {  
        ft_printf("Too many arguments\n");
        return (1);
    }
    i = 0;
    while(cmd[1] && cmd[1][i])
    {
        if (i == 0 && cmd[1][i] == '-')
            i++;
        else if (!ft_isdigit(cmd[1][i]))
        {
		    write(STDERR_FILENO, "minishell: exit: ", ft_strlen("minishell: exit: "));
	        write(STDERR_FILENO, cmd[1], ft_strlen(cmd[1]));
		    write(STDERR_FILENO, ": numeric argument required\n", ft_strlen(": numeric argument required\n"));
            exit (255);
        }
        i++;
    }
    if (cmd[1])
        exit(ft_atoi(cmd[1]));
    exit(EXIT_SUCCESS);
}