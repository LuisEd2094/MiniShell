/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:10:56 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/02 12:11:30 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_arguments_internal.h"

int get_cmd_count(char **cmds)
{
    int cmd_count;

    cmd_count = 0;
    while(cmds[cmd_count])
        cmd_count++;
    return (cmd_count);
}

int ft_commands_count(char *input)
{
    int i;
    int count;

    i = -1;
    count = 1;
    while(input[++i])
    {
        if (input[i] == '"' || input[i] == '\'')
            i += get_quotes_size(&input[i]) - 1;
        else if (input[i] == '|')
            count++;
    }
    return (count);
}


void *free_cmds_error(char **cmds)
{
    int i;

    i = 0;
    while(cmds[i])
        free(cmds[i++]);
    free(cmds);
    return (NULL); //retutrn errr number, perror
}


int get_cmd_size(char *input, int i)
{
    int start;

    start = i;
    while(input[i])
    {
        if (input[i] == '"' || input[i] == '\'')
            i += get_quotes_size(&input[i]) - 1;
        if (input[i] == '|')
            break ;
        i++;
    }
    return (i - start);
}


char    *get_cmd(char *input, int *i)
{
    int     j;
    int     cmd_size;
    char    *new_cmd;

    cmd_size = get_cmd_size(input, *(i));
    new_cmd = (char *)malloc(sizeof(char) * cmd_size + 1);
    if (!new_cmd)
        return (NULL);
    j = 0;
    while(j < cmd_size)
    {
        new_cmd[j] = input[*(i)];
        *(i) += 1;
        j++;
    }
    *(i) += 1;
    new_cmd[j] = '\0';
    return (new_cmd);
}

char    **ft_commands_split(char *input)
{
    int     cmd_count;
    int     i;
    int     j;
    char    **cmds;
    
    cmd_count = ft_commands_count(input);
    cmds = (char **)malloc(sizeof(char *) * (cmd_count + 1));
    if (!cmds)
        return (NULL);
    i = 0;
    j = 0;
    while (j < cmd_count)
    {
        cmds[j] = get_cmd(input, &i);
        if (!cmds[j])
            return (free_cmds_error(cmds));
        j++;
    }
    cmds[j] = NULL;
    return (cmds);
}

char ***get_cmds_value(char *input)
{
    char    ***cmds;
    char    **split_input_pipe;
    int     cmd_count;
    int     i;

    split_input_pipe = ft_commands_split(input);
    if (!split_input_pipe)
        exit (1);
    cmd_count = get_cmd_count(split_input_pipe);
    cmds = (char ***)malloc(sizeof(char **) * (cmd_count + 1));
    if (!cmds)
        exit (1);
    i = 0;
    while (i < cmd_count)
    {
        cmds[i] = get_cmd_argument(split_input_pipe[i]);
        if (!cmds[i])
            exit (1);
        free(split_input_pipe[i]);
        i++;
    }
    free(split_input_pipe);
    cmds[i] = NULL;
    return  (cmds);
}