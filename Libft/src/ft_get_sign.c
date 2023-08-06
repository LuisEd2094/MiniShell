int	get_sign(char *argv)
{
	int	sign;
	int i;

	sign = 0;
	i = 0;
	if ((argv[i] == '-' || argv[i] == '+'))
	{
		if (argv[i] == '-' )
			sign = -1;
		else if (argv[i] == '+')
			sign = 1;
	}
	else
		sign = 0;
	return (sign);
}