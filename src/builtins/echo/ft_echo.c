#include "./MS_functions.h"

int	ft_echo(char **arguments)
{
	int	i;
	int	flag_n;

	i = 1;
	flag_n = 0;
	if (arguments == NULL)
		return -1;
	if (i < arguments && ft_strcmp(arguments[i], "-n") == 0) 
	{
		flag_n = 1;
		i++;
	}
	while (arguments[i] != NULL ) 
	{
		ft_printf("%s", arguments[i++]);
		if (arguments[i] != NULL) 
			ft_printf(" ");
	}
	if (!flag_n)
		ft_printf("\n");
	return 0;
}
