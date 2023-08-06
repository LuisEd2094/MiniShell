/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 16:24:49 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/07/05 10:01:14 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

void	*ft_free_strs_line(char **str, char **str2);
char	*get_next_line(int fd, int b_size);
char	*read_file(int fd, char *buffer, int bytes_read, int b_size);
char	*join_buff(char *buffer, char *reader);
char	*buffer_prep(char *buffer);
char	*parse_line(char *buffer);

#endif
