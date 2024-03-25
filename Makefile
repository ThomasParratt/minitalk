# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tparratt <tparratt@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/13 17:20:21 by tparratt          #+#    #+#              #
#    Updated: 2024/02/21 09:21:49 by tparratt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CLIENT		=	client
SERVER		=	server

LIBFT		=	libft/libft.a

CLIENT_SRC	=	client.c
SERVER_SRC	=	server.c

CLIENT_OBJ	=	$(CLIENT_SRC:.c=.o)
SERVER_OBJ	=	$(SERVER_SRC:.c=.o)

CC			=	cc

RM			=	rm -f

CFLAGS		=	-Wall -Wextra -Werror

all:		$(CLIENT) $(SERVER)

$(CLIENT):	$(CLIENT_OBJ)
			make -C ./libft
			$(CC) $(CFLAGS) -o $(CLIENT) $(CLIENT_OBJ) $(LIBFT)

$(SERVER):	$(SERVER_OBJ)
			make -C ./libft
			$(CC) $(CFLAGS) -o $(SERVER) $(SERVER_OBJ) $(LIBFT)

clean:
			make clean -C libft
			$(RM) $(CLIENT_OBJ) $(SERVER_OBJ)

fclean: 	clean
			make fclean -C libft
			$(RM) $(CLIENT) $(SERVER)

re:			fclean all

.PHONY:		all clean fclean re