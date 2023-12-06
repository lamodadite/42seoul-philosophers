# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/14 18:53:46 by jongmlee          #+#    #+#              #
#    Updated: 2023/12/06 12:54:31 by jongmlee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo
SRC_DIR := srcs
SRCS := main_bonus.c init_bonus.c process_bonus.c utils_bonus.c
OBJ_DIR := objs
OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
INC_DIR := incs
INCS := philosophers_bonus.h
CC := cc
CFLAGS := -Wall -Wextra -Werror
LDFLAGS := -I $(INC_DIR)

all : $(NAME)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(addprefix $(INC_DIR)/, $(INCS))
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(LDFLAGS) -c -o $@ $<

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

bonus : $(NAME)

clean :
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
