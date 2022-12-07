/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdameros <tdameros@student.42lyon.f>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 23:01:12 by tdameros          #+#    #+#             */
/*   Updated: 2022/12/06 23:01:13 by tdameros         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

static char	*join_char_in_list(t_list **list, size_t len);

/**
 * Join the char list and write the message in stdout.
 * SIGUSER2 signal is send to the client as delivery receipt.
 * message structure is reset by default even there is an error.
 * If an error is encountered the function write the error message in stderr
 * and exit with failure status.
 */
void	display_message(t_message *message)
{
	message->message = join_char_in_list(&message->list, message->len);
	if (message->message == NULL)
	{
		reset_message(message);
		return (raise_error(MALLOC_ERROR));
	}
	if (write(1, message->message, message->len) < 0)
	{
		reset_message(message);
		return (raise_error(WRITE_ERROR));
	}
	reset_message(message);
	if (kill(message->client_pid, SIGUSR2) < 0)
		raise_error(KILL_ERROR);
}

/**
 * Join a reverse char list
 * (the first node is the last character of the string).
 * @return allocated char *, otherwise NULL
 */
static char	*join_char_in_list(t_list **list, size_t len)
{
	char	*str_join;
	char	*c;
	t_list	*node;

	str_join = malloc(sizeof(*str_join) * (len + 1));
	if (str_join == NULL)
		return (NULL);
	node = *list;
	str_join[len--] = '\0';
	while (node != NULL)
	{
		c = node->content;
		str_join[len] = *c;
		len--;
		node = node->next;
	}
	return (str_join);
}

/**
 * Free char list, message and set all properties to 0.
 */
void	reset_message(t_message *message)
{
	ft_lstclear(&message->list, free);
	free(message->message);
	message->byte = 0;
	message->index_byte = 0;
	message->len = 0;
}

/**
 * Malloc the char and push it in front of the list.
 * @return the value 0 if successful; otherwise the value -1 indicate an error
 */
int	push_char_in_list(t_list **list, char c)
{
	char	*malloc_char;
	t_list	*node;

	malloc_char = malloc(sizeof(*malloc_char) * 1);
	if (malloc_char == NULL)
		return (0);
	malloc_char[0] = c;
	node = ft_lstnew(malloc_char);
	if (node == NULL)
	{
		free(malloc_char);
		return (0);
	}
	ft_lstadd_front(list, node);
	return (1);
}

/**
 * Write the message followed by a \n in stderr and exit with failure status.
 */
void	raise_error(char *message)
{
	ft_putendl_fd(message, STDERR_FILENO);
	exit(EXIT_FAILURE);
}
