#include <parse_arguments.h>
#include "parse_internal.h"

bool check_if_start_word(char c)
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


int get_cmd_count(char *input, int i)
{
    int j;
    int num_cmds;

    j = i;
    num_cmds = 0;
    while(input[j])
    {
        while (input[j] && ft_isspace(input[j]))
            j++;
        
    }

}


char *get_cmd_argument(char *input, int *start, int end)
{
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
            while(input[i] != quote)
            {
                printf("%c", input[i]);
                i++;
            }
            printf("\n");

            i++;
            continue;
        }
        j = i;
        while (input[i] && ft_isascii(input[i]) && !ft_isspace(input[i]))
        {
            printf("%c", input[i]);
            i++;
        }
        printf(" [%i] size\n", i - j);
    }
    *start = i;

}


char **get_cmd_value_and_prep(char *input, int start, int end)
{
    char            **new_cmd;
    int             save_start;
    int             cmd_count;
    int             out_files_count;
    int             in_files_count;


    cmd_count = 0;
    save_start = start;
    if (input [start] == '|')
    {
        start++;
    }
    while (input[start] && start <= end)
    {
        while (ft_isspace(input[start]) && input[start])
            start++;
        if (input[start] == '>')
        {
            if (input[start + 1] == '>')
                start += 2;
            else
                start++;
            while(ft_isspace(input[start]))
                start++;
            
            /*if (input[start] == '>' && input[start + 1] == '>')
                continue;
            else
                continue;*/
            while (input[start] && ft_isascii(input[start]) && !ft_isspace(input[start]))
            {
                start++;
            }   
            continue;
        }
        if (input[start] == '|')
        {
            start++;
            continue; 
        }
        if (input[start] == '"' || input[start] == '\'')
        {
            char quote = input[start];
            start++;
            while(input[start] != quote)
            {
                printf("%c", input[start]);
                start++;
            }
            printf("\n");

            start++;
            cmd_count++;
            continue;
        }
        while (input[start] && ft_isascii(input[start]) && !ft_isspace(input[start]))
        {
            printf("%c", input[start]);
            start++;
        }   
        cmd_count++;
        printf("\n");
    }
    new_cmd = (char **)malloc(sizeof(char *) * cmd_count + 1);
    if (!new_cmd)
        exit(1);
    int i = 0;
    while(i < cmd_count)
    {
        new_cmd[i] = get_cmd_argument(input, &save_start, end);
        i++;
    }
    printf("cmd_count [%i]\n", cmd_count);
    return NULL;
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
            j = i;
        }
        i++;
    }
    /*    
    temp = cmd_list;
    while (input[pos])
    {
        cmd = get_cmd_value(input, &pos);
        if (!cmd)
            exit(1);
        temp = ft_lstnew(cmd);
        if (!temp)
            exit(1);
        temp = temp->next;

*/


    printf("%s\n", input);
    return 1;
}


int main(int argc, char **argv)
{
    printf("%s\n", argv[1]);
    execute_input(argv[1]);
}