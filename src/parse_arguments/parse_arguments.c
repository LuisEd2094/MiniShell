#include <parse_arguments.h>
#include "parse_internal.h"

int check_if_start_word(char c)
{
    char    *values_to_check;
    int     i;

    i = 0;
    values_to_check = "\"\'>< |&";
    while (values_to_check[i])
    {
        printf("%c ", values_to_check[i]);
        i++;
    }
    printf("\n");
    return (1);
}


void    skip_redirection(char *input, int *start)
{
    int i;

    i = 0;

    if (input[i + 1] == '>')
        i += 2;
    else
        i++;
    while(ft_isspace(input[i]))
        i++;
    /*if (input[start] == '>' && input[start + 1] == '>')
        continue;
    else
        continue;*/
    while (input[i] && ft_isascii(input[i]) && !ft_isspace(input[i]))
    {
        i++;
    }
    *start += i;   
}

char *get_cmd_argument(char *input, int *start, int end)
{
    char    *new;
    int i;
    int j;

    i = *start;
    j = *start;
    if(input[i] == '|')
        i++;
    while (input[i] && i <= end)
    {
        while (ft_isspace(input[i]) && input[i])
            i++;
        if (input[i] == '>')
        {
            skip_redirection(&input[i], &i);
            continue;
        }
        if (input[i] == '|')
        {
            i++;
            continue; 
        }
        if (input[i] == '"' || input[i] == '\'')
        {

            char quote = input[i];
            i++;
            j = i;
            while(input[i] != quote)
            {
                //printf("%c", input[i]);
                i++;
            }
            new = (char *)malloc(sizeof(char) * i - j + 1);
            if (!new)
                return(NULL);
            ft_strlcpy(new, &input[j], i - j + 1);
            i++;
            *start = i;

            //printf(" [%i] size\n", i - 1 - j);

            return (new);
        }
        j = i;
        while (input[i] && ft_isascii(input[i]) && !ft_isspace(input[i]))
        {
            //printf("%c", input[i]);
            i++;
        }
       // printf(" [%i] size\n", i - j);
        new = (char *)malloc(sizeof(char) * i - j + 1);
        if (!new)
            return(NULL);
        ft_strlcpy(new, &input[j], i - j +1);
        *start = i;
        return (new);
    }

}


int    handle_redirection(char *input, int *start)
{
    int i;

    i = 0;
    if (input[i + 1] == '>')
        i += 2;
    else
        i++;
    while(ft_isspace(input[i]))
        i++;

    /*if (input[start] == '>' && input[start + 1] == '>')
    continue;
    else
    continue;*/
    while (input[i] && ft_isascii(input[i]) && !ft_isspace(input[i]))
    {
        i++;
    }
    *start += i;
    return (1); 
}

void    handle_quotes(char *input, int *start)
{
    char    quote;
    int     i;
    
    i = 0;
    quote = input[i];
    i++;
    
    while(input[i] != quote)
    {
        i++;
    }
    //printf("\n");

    i++;
    *start += i;
}

int get_cmd_count_and_handle_redirections(char *input, int start, int end, int *og_count)

{
    int cmd_count;
    
    cmd_count = 0;
    if (input [start] == '|')
    {
        //should start STDIN PIPE
        start++;
    }
    while (input[start] && start <= end)
    {
        while (ft_isspace(input[start]) && input[start])
            start++;
        if (input[start] == '>')
        {
            if (!handle_redirection(&input[start], &start))
                return (0);
            continue;
        }
        if (input[start] == '|')
        {
            start++;
            continue; 
        }
        if (input[start] == '"' || input[start] == '\'')
        {
            handle_quotes(&input[start], &start);
            cmd_count++;
            continue;
        }
        while (input[start] && ft_isascii(input[start]) && !ft_isspace(input[start]))
        {
            start++;
        }   
        cmd_count++;
    }
    *og_count = cmd_count;
    return (1);
}


char **get_cmd_value_and_prep(char *input, int start, int end)
{
    char    **new_cmd;
    int     save_start;
    int     cmd_count;
    int     i;


    if (!get_cmd_count_and_handle_redirections(input, start, end, &cmd_count))
        return (NULL);
    new_cmd = (char **)malloc(sizeof(char *) * cmd_count + 1);
    if (!new_cmd)
        return(NULL);
    save_start = start;
    i = 0;
    while(i < cmd_count)
    {
        new_cmd[i] = get_cmd_argument(input, &save_start, end);
        if (!new_cmd[i])
        {
            return (NULL);
        }
        i++;
    }
    new_cmd[i] = NULL;
    return (new_cmd);
}


int execute_input(char *input)
{
    char            **cmd;
    int     i;
    int     j;

    i = 0;
    j = 0;
    while (input[i])
    {
        if (input[i] == '|' || !input[i + 1])
        {
            cmd = get_cmd_value_and_prep(input, j, i);
            if (!cmd)
            {
                printf("IM HERE\n");
                return (errno);

            }
            j = i;
            printf("GOT CMDS: \n");
            for (int k = 0; cmd[k]; k++)
            {
                printf("[%s]\n", cmd[k]);
            }
        }
        i++;
    }
    printf("%s\n", input);
    return (0); // should return 0 if no fail, so mini shell can save the last error,
}


int main(int argc, char **argv)
{
    printf("%s\n", argv[1]);
    execute_input(argv[1]);
}