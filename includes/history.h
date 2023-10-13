/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lsoto-do <lsoto-do@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 11:04:44 by lsoto-do          #+#    #+#             */
/*   Updated: 2023/10/13 11:05:52 by lsoto-do         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HISTORY_H
# define HISTORY_H
# include <libft.h>
# include "../readline/readline.h"
# include "../readline/history.h"

typedef enum s_order
{
	INIT,
	UPDATE,
	CLOSE,
}	t_order;

void	work_history(int order, char *input);
#endif
