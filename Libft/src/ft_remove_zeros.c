void remove_zeros(char *str)
{
	int i;
    int k;

    i = 0;
	if (str[i] == '+' || str[i] == '-')
        i++;
	if (str[i] != '0')
		return ;
	k = i;
	while (str[i] == '0')
		i++;
	while (str[i])
		str[k++] = str[i++];
	while (str[k])
		str[k++] = '\0';
}