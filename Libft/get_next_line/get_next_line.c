/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:24:17 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/06/20 16:24:18 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/libft.h"

char	*parse_line(char *buffer)
{
	char	*line;
	int		i;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] && buffer[i] == '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*buffer_prep(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (ft_free_strs_line(&buffer, 0));
	line = ft_calloc((ft_strlen(buffer) - i + 1), sizeof(char));
	if (!line)
		return (ft_free_strs_line(&buffer, 0));
	i++;
	j = 0;
	while (buffer[i])
		line[j++] = buffer[i++];
	ft_free_strs_line (&buffer, 0);
	return (line);
}

char	*join_buff(char *buffer, char *reader)
{
	char	*temp;

	temp = ft_strjoin(buffer, reader);
	if (!temp)
		return (ft_free_strs_line(&buffer, &reader));
	ft_free_strs_line(&buffer, 0);
	return (temp);
}

char	*read_file(int fd, char *buffer, int bytes_read, int b_size)
{
	char	*reader;

	reader = ft_calloc(b_size + 1, sizeof(char));
	if (!reader)
		return (ft_free_strs_line(&buffer, &reader));
	while (bytes_read > 0)
	{
		bytes_read = read(fd, reader, b_size);
		if (bytes_read == -1)
			return (ft_free_strs_line(&buffer, &reader));
		reader[bytes_read] = '\0';
		buffer = join_buff(buffer, reader);
		if (!buffer)
			return (NULL);
		if (ft_strchr(reader, '\n'))
			break ;
	}
	ft_free_strs_line(&reader, 0);
	return (buffer);
}

char	*get_next_line(int fd, int b_size)
{
	static char	*buffer[4096];
	char		*line;
	int			bytes_read;

	if (fd < 0)
		return (NULL);
	if (b_size <= 0)
	{
		if (buffer[fd])
			ft_free_strs_line(&buffer[fd], 0);
		return (NULL);
	}
	if (!buffer[fd])
		buffer[fd] = ft_calloc(1, 1);
	if (!buffer[fd])
		return (ft_free_strs_line(&buffer[fd], 0));
	bytes_read = 1;
	buffer[fd] = read_file(fd, buffer[fd], bytes_read, b_size);
	if (!buffer[fd])
		return (NULL);
	line = parse_line(buffer[fd]);
	if (!line || *line == '\0')
		return (ft_free_strs_line(&buffer[fd], &line));
	buffer[fd] = buffer_prep(buffer[fd]);
	return (line);
}
