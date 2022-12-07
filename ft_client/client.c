/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 23:42:48 by tdameros          #+#    #+#             */
/*   Updated: 2022/12/06 23:42:49 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

//
// Created by Tom Damerose on 12/3/22.
//
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "client.h"

pid_t	g_server_pid;

static void	delivery_receipt_controller(int sig, siginfo_t *info, void *uap);
static int	send_message(pid_t pid, char *message, useconds_t microseconds);
static int	send_byte(pid_t	pid, unsigned char byte, useconds_t microseconds);
static void	raise_error(char *message);

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc == 3)
	{
		sa.sa_flags = SA_SIGINFO;
		sigemptyset(&sa.sa_mask);
		sa.sa_sigaction = &delivery_receipt_controller;
		if (sigaction(SIGUSR1, &sa, NULL) < 0
			|| sigaction(SIGUSR2, &sa, NULL) < 0)
			raise_error(SA_ERROR);
		g_server_pid = ft_atoi(argv[1]);
		if (g_server_pid == 0)
			raise_error(KILL_ERROR);
		if (send_message(g_server_pid, argv[2], USLEEP) < 0)
			raise_error(KILL_ERROR);
	}
	else
		raise_error(ARGS_ERROR);
	return (0);
}

/**
 * Sigaction handler who listen SIGUSR1 and SIGURS2.
 * SIGUSER1 is the bit delivery receipt sent by the server.
 * SIGUSER2 is the message delivery receipt sent by the server.
 */
static void	delivery_receipt_controller(int sig, siginfo_t *info, void *uap)
{
	(void) uap;
	if (sig == SIGUSR2 && info->si_pid == g_server_pid)
		ft_printf("%s\n", DELIVERY_RECEIPT);
	else if (info->si_pid != g_server_pid)
		pause();
}

/**
 * Sends each bit of the message using signals.
 * SIGUSER1 means 0
 * SIGUSER2 means 1
 * @param microseconds between each signal
 * return the value 1 if successful; otherwise the value -1 indicate an error
 */
static int	send_message(pid_t pid, char *message, useconds_t microseconds)
{
	size_t	index;

	index = 0;
	while (message[index] != '\0')
	{
		if (send_byte(pid, message[index], microseconds) < 0)
			return (-1);
		index++;
	}
	return (send_byte(g_server_pid, 0, microseconds));
}

/**
 * Sends each bit of the byte using signals.
 * @param microseconds between each signal
 * @return the value 0 if successful; otherwise the value -1 indicate an error
 */
static int	send_byte(pid_t	pid, unsigned char byte, useconds_t microseconds)
{
	int	index_bit;
	int	bit;
	int	sig;

	index_bit = SIZE_BYTE - 1;
	while (index_bit >= 0)
	{
		bit = (byte >> index_bit) & 1;
		usleep(microseconds);
		if (bit == 0)
			sig = SIGUSR1;
		else
			sig = SIGUSR2;
		if (kill(pid, sig) < 0)
			return (-1);
		pause();
		index_bit--;
	}
	return (0);
}

/**
 * Write the message followed by a \n in stderr and exit with failure status.
 */
static void	raise_error(char *message)
{
	ft_putendl_fd(message, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
