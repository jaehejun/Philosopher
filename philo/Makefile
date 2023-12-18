# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaehejun <jaehejun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/06 20:17:35 by jaehejun          #+#    #+#              #
#    Updated: 2023/12/12 19:08:15 by jaehejun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo

CC		= CC

CFLAGS	= -Wall -Wextra -Werror #-fsanitize=thread -g

SRCS	=	main.c\
			philo_utils.c\
			initialize.c\
			philo_action.c\
			monitoring.c\

OBJS	= $(SRCS:.c=.o)

all		: $(NAME)

$(NAME)	: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re:
	make fclean
	make all

.PHONY = all clean fclean re