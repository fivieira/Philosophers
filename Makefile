# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: fivieira <fivieira@student.42.fr>          +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2024/04/19 12:36:02 by fivieira          #+#    #+#             #
#   Updated: 2024/04/19 12:36:27 by fivieira         ###   ########.fr       #
#                                                                            #
# ************************************************************************** #

NAME = philo

SRC = 	source/philo.c \
    	source/check.c \
    	source/init_data.c \
    	source/routine.c \
    	source/time.c \
		source/utils.c \
    	source/monitor.c \
       	source/eat1.c \
		source/eat2.c \
    	source/sleep.c \
		source/think.c \
    	source/getter1.c \
    	source/getter2.c \
    	source/setters.c

OBJS = ${SRC:.c=.o}

#INCLUDE = -I .

CC = gcc

RM = rm -f

CFLAGS = -Wall -Wextra -Werror -Iincludes/

MAKE = make -C

all:	${NAME}

$(NAME): ${OBJS}
		$(CC) $(CFLAGS) $(SRC) -o $(NAME)

clean:
		${RM} ${OBJS}


fclean: clean
		${RM} ${NAME}


re: fclean all

.PHONY: all clean fclean re