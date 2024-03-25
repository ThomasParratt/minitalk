/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:06:10 by tparratt          #+#    #+#             */
/*   Updated: 2024/02/13 16:06:10 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_signal(int pid, unsigned char character)
{
	int				i;
	unsigned char	temp_char;

	i = 8;
	temp_char = character;
	while (i > 0)
	{
		i--;
		temp_char = character >> i;
		if (temp_char % 2 == 0)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		usleep(42);
	}
}

int	main(int argc, char *argv[])
{
	pid_t		server_pid;
	const char	*message;
	int			i;

	if (argc == 3)
	{
		server_pid = ft_atoi(argv[1]);
		message = argv[2];
		i = 0;
		while (message[i])
		{
			send_signal(server_pid, message[i]);
			i++;
		}
		send_signal(server_pid, '\0');
	}
	else
		ft_printf("Enter: ./client <PID> <message>\n");
	return (0);
}
