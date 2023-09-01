#include "execute_internal.h"


void handle_double_quote(char *input, t_quote *quote_info, t_minishell *mini)
{
    int i;
    int j;

    i = 1;
    j = i;
    ft_printf(" start of quoted arg [%s]\n", input);

    while (input[i] && input[i] != quote_info->quote)
    {
        if (input[i] == '$')
        {
            quote_info->env = get_env_str(&input[i + 1], mini->env_list);
            //ft_printf("before ascci [%s] [%i] \n", &input[i], i);
            i += get_ascii_size(&input[i]);
            //ft_printf("env [%s] [%s]\n",quote_info->env, &input[i]);
            free(quote_info->env);
        }  
        i++;
    }
    if (input[i] == quote_info->quote)
        i++;
    ft_printf("[%i] quote [%c] after loop [%s]\n",i, quote_info->quote, &input[i]);
    quote_info->new = malloc(sizeof(char) * 2);
    quote_info->new[0] = 'A';
    quote_info->new[1] = '\0';
    quote_info->i = i;
}


void handle_single_quote(char *input, t_quote *quote_info)
{
    int i;
    int j;

    i = 1;
    j = i;
    while(input[i] && input[i] != quote_info->quote)
        i++;
    quote_info->new = (char *)malloc(sizeof(char) * i - j + 1);
    if (!quote_info->new)
        return;
    ft_strlcpy(quote_info->new, &input[j], i - j + 1);
    i++;
    quote_info->i = i;
}


char *get_quoted_arg(char *input, int *start, t_minishell *mini)
{
    t_quote quote_info;

    quote_info.quote = input[0];
    quote_info.new = NULL;
    if (quote_info.quote == '\"')
        printf("Need to handle double quote \n");//handle_double_quote(input, &quote_info, mini);
    else
        handle_single_quote(input, &quote_info);
    if (!quote_info.new)
        return (NULL);
    *start = quote_info.i;
    printf("%i start [%s] \n", *start, &input[*start]);
    return (quote_info.new);
}