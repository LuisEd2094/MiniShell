static int	check_last_digit(int sign, char *argv, int i)
{
	if (argv[i + 1] != '\0')
		return (0);
	if (sign == -1)
	{
		if ('8' - argv[i] >= 0)
			return (1);
		return (0);
	}
	else
	{	
		if ('7' - argv[i] >= 0)
			return (1);
		return (0);
	}
}

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static int	get_sign(char *argv)
{
	int	sign;
	int i;

	sign = 0;
	i = 0;
	if ((argv[i] == '-' || argv[i] == '+') && ft_isdigit(argv[i + 1]))
	{
		if (argv[i] == '-' )
			sign = -1;
		else if (argv[i] == '+')
			sign = 1;
		i++;
	}
	else
		sign = 0;
	return (sign);
}

int	check_if_int(char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = get_sign(str);
	if (sign)
		i++;
	while (str[i])
	{
		if ((sign && i == 10) || (!sign && i == 9))
			return (check_last_digit(sign, str, i));
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}