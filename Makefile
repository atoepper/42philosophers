# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/22 10:49:48 by atoepper          #+#    #+#              #
#    Updated: 2025/09/19 14:24:45 by atoepper         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_DIR = srcs
INC_DIR = incl
SRC =	main.c \
		error.c \
		free.c \
		init.c \
		monitor.c \
		parse.c \
		philo_routine.c \
		philo_routine2.c \
		threads.c \
		time.c \
		utils.c \

SRC := $(patsubst %.c, $(SRC_DIR)/%.c, $(SRC))

CC = cc
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -g -fPIE 
CFLAGS += -I$(INC_DIR)

OBJ_DIR = .obj
OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

all : ${NAME}

$(NAME) : $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f ${NAME}

re: fclean
	$(MAKE) all

v: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

.PHONY : all clean fclean re v 

