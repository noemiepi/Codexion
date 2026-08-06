# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: npillet <npillet@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/05/14 14:31:03 by npillet           #+#    #+#              #
#    Updated: 2026/08/06 14:50:21 by npillet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = codexion
CC = cc
CFLAGS = -g -Wall -Werror -Wextra -pthread
INC = -I src/include

SRC =	codexion.c					\
		parser/arg_parse.c			\
		parser/parsing.c			\
		scheduler/scheduler_edf.c	\
		scheduler/scheduler_fifo.c	\
		coders/create_coders.c		\
		coders/coders.c				\
		coders/dongles.c			\
		coders/monitoring.c			\
		coders/mutexes.c			\
		coders/threads.c			\
		utils/priority.c			\
		utils/getter.c				\
		utils/free.c				\
		utils/ft_atoi.c				\
		utils/debug.c


OBJ_PATH = obj/
SRC_PATH = src/

SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJ = $(SRC:.c=.o)
OBJS = $(patsubst $(SRC_PATH)%.c, $(OBJ_PATH)%.o, $(SRCS))

.PHONY: all clean fclean re
.SILENT:

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(NAME)

re: fclean all
