/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:35:56 by tdameros          #+#    #+#             */
/*   Updated: 2022/12/05 14:36:20 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <stddef.h>
# include "../libft/incs/libft.h"
# include "../libft/incs/ft_printf.h"

# define KILL_ERROR "Kill Error"
# define MALLOC_ERROR "Malloc Error"
# define SA_ERROR "Sigaction Error"
# define WRITE_ERROR "Write Error"

# define USLEEP 50
# define SIZE_BYTE 8

typedef struct s_message
{
	char	*message;
	char	byte;
	size_t	len;
	int		index_byte;
	t_list	*list;
	int		client_pid;
}	t_message;

void	display_message(t_message *message);
void	reset_message(t_message *message);
int		push_char_in_list(t_list **list, char c);
void	raise_error(char *message);

#endif
