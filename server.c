/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 16:05:59 by tparratt          #+#    #+#             */
/*   Updated: 2024/02/13 16:05:59 by tparratt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	print_and_free(char **received_message)
{
	ft_printf("%s\n", *received_message);
	free(*received_message);
	*received_message = ft_strdup("");
	if (*received_message == NULL)
		exit(0);
}

static void	join_and_free(char **received_message, char current_char)
{
	char	*temp;
	char	temp_arr[2];

	temp_arr[0] = current_char;
	temp_arr[1] = '\0';
	temp = ft_strjoin(*received_message, temp_arr);
	if (temp == NULL)
		exit(0);
	free(*received_message);
	*received_message = temp;
}

static void	handle_signal(int signal)
{
	static unsigned char	current_char;
	static int				bit_index;
	static char				*received_message;

	if (!received_message)
	{
		received_message = ft_strdup("");
		if (received_message == NULL)
			exit(0);
	}
	current_char |= (signal == SIGUSR1);
	bit_index++;
	if (bit_index == 8)
	{
		if (current_char == '\0')
			print_and_free(&received_message);
		else
			join_and_free(&received_message, current_char);
		bit_index = 0;
		current_char = 0;
	}
	else
		current_char <<= 1;
}

int	main(void)
{
	ft_printf("Server Process ID: %d\n", getpid());
	signal(SIGUSR1, handle_signal);
	signal(SIGUSR2, handle_signal);
	while (1)
		pause();
	return (0);
}
