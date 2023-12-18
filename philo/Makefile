# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/14 18:53:46 by jongmlee          #+#    #+#              #
#    Updated: 2023/12/07 18:40:20 by jongmlee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo
SRC_DIR := srcs
SRCS := main.c utils.c init.c thread.c monitor.c
OBJ_DIR := objs
OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
INC_DIR := incs
INCS := philosophers.h
CC := cc
CFLAGS := -Wall -Wextra -Werror
LDFLAGS := -I $(INC_DIR)

all : $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(addprefix $(INC_DIR)/, $(INCS))
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $<

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
