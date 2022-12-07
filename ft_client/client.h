/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 23:42:52 by tdameros          #+#    #+#             */
/*   Updated: 2022/12/06 23:42:53 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "../libft/incs/ft_libc.h"

# define SA_ERROR "Sigaction Error"
# define KILL_ERROR "Kill Error: Please use a valid server pid."
# define DELIVERY_RECEIPT "The server has received and displayed the message."
# define ARGS_ERROR "Usage: ./client [server_pid] [message]"

# define USLEEP 10
# define SIZE_BYTE 8

#endif
