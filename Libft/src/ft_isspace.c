int ft_isspace(char chr)
{
    if (chr == '\f' || chr == '\n' \
		|| chr == '\r' || chr == '\v' \
		|| chr == '\t' || chr == ' ' \
    || chr == '\b')
    {
        return (1);
    }
    return (0);
}