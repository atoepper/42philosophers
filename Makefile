# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atoepper <atoepper@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/14 14:49:59 by atoepper          #+#    #+#              #
#    Updated: 2024/06/04 12:59:56 by atoepper         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

### COMPILATION ###
CC      = gcc -O2
FLAGS  = -Wall -Wextra -Werror -g

### EXECUTABLE ###
NAME   = philo

### INCLUDES ###
OBJ_PATH  = objs
HEADER = incl
SRC_PATH  = srcs

### SOURCE FILES ###
SOURCES = philo.c \
			philo_utils.c \
			philo_time.c \
			philo_init.c \
			philo_monitor.c \
			philo_routine.c \
			philo_threads.c

### OBJECTS ###

SRCS = $(addprefix $(SRC_PATH)/,$(SOURCES))
OBJS = $(addprefix $(OBJ_PATH)/,$(SOURCES:.c=.o))

### COLORS ###
NOC         = \033[0m
RED         = \033[1;31m
GREEN       = \033[1;32m
BLUE        = \033[1;34m
CYAN        = \033[1;36m
WHITE       = \033[1;37m

### RULES ###

all: tmp $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $@ $^
	@echo "$(GREEN)Project successfully compiled"

tmp:
	@mkdir -p objs

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEADER)/$(NAME).h | tmp
	@$(CC) $(FLAGS) -c -o $@ $<
	@echo "$(BLUE)Creating object file -> $(WHITE)$(notdir $@)... $(RED)[Done]$(NOC)"

clean:
	@rm -rf $(OBJ_PATH)

fclean:
	@rm -rf $(OBJ_PATH)
	@rm -f $(NAME)

re: fclean 
	@$(MAKE) all

.PHONY: tmp, re, fclean, clean
