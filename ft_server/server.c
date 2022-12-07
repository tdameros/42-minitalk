/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 23:01:19 by tdameros          #+#    #+#             */
/*   Updated: 2022/12/06 23:01:20 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "server.h"

static void	message_controller(int sig, siginfo_t *info, void *uap);

int	main(void)
{
	struct sigaction	sa;
	pid_t				pid;

	sa.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = &message_controller;
	if (sigaction(SIGUSR1, &sa, NULL) < 0 || sigaction(SIGUSR2, &sa, NULL) < 0)
		raise_error(SA_ERROR);
	pid = getpid();
	ft_printf("PID: %d\n", pid);
	while (1)
		pause();
}

/**
 * Signaction handler who listen SIGUSER1 and SIGUSER2.
 * SIGUSER1 is the bit 0 sent by the client.
 * SIGUSER2 is the bit 1 sent by the server.
 */
static void	message_controller(int sig, siginfo_t *info, void *uap)
{
	static t_message	message;

	(void) uap;
	if (info->si_pid != 0)
		message.client_pid = info->si_pid;
	message.byte = (message.byte << 1) + (sig == SIGUSR2);
	message.index_byte++;
	if (message.index_byte == SIZE_BYTE && message.byte == 0)
		return (display_message(&message));
	else if (message.index_byte == SIZE_BYTE)
	{
		if (!push_char_in_list(&message.list, message.byte))
			return (reset_message(&message), raise_error(MALLOC_ERROR));
		message.index_byte = 0;
		message.byte = 0;
		message.len++;
	}
	usleep(USLEEP);
	if (kill(message.client_pid, SIGUSR1) < 0)
		return (reset_message(&message), raise_error(KILL_ERROR));
}
