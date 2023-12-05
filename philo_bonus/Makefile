# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jongmlee <jongmlee@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/14 18:53:46 by jongmlee          #+#    #+#              #
#    Updated: 2023/12/05 21:50:53 by jongmlee         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME:=philo

SRC_DIR:=srcs
SRCS:=main_bonus.c utils_bonus.c init_bonus.c process_bonus.c
INC_DIR:=incs
INCS:=philosophers_bonus.h

CC:=cc
CFLAGS:=-Wall -Wextra -Werror #-g3 -fsanitize=thread

$(NAME) : $(addprefix $(SRC_DIR)/, $(SRCS)) $(addprefix $(INC_DIR)/, $(INCS))
	$(CC) $(CFLAGS) -o $@ $(addprefix $(SRC_DIR)/, $(SRCS)) -I $(INC_DIR)

.PHONY : all clean fclean re bonus

all : $(NAME)

clean :
# 채워야 하는데..

fclean : clean
	rm -f $(NAME)

re : fclean all
