# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/14 18:53:46 by jongmlee          #+#    #+#              #
#    Updated: 2023/11/30 23:20:42 by jongmlee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:=philo

SRC_DIR:=srcs
SRCS:=main.c utils.c init.c
INC_DIR:=incs
INCS:=philosophers.h

CC:=cc
CFLAGS:=-Wall -Wextra -Werror

$(NAME) : $(addprefix $(SRC_DIR)/, $(SRCS)) $(addprefix $(INC_DIR)/, $(INCS))
	$(CC) $(CFLAGS) -g -o $@ $(addprefix $(SRC_DIR)/, $(SRCS)) -I $(INC_DIR)

.PHONY : all clean fclean re bonus

all : $(NAME)

clean :
# 채워야 하는데..	

fclean : clean
	rm -f $(NAME)

re : fclean all
