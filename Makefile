# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ymomen <ymomen@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/19 00:41:48 by ymomen            #+#    #+#              #
#    Updated: 2023/11/22 23:16:58 by ymomen           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC =  get_next_line_utils.c get_next_line.c
SRC_B = get_next_line_utils_bonus.c get_next_line_bonus.c
OBJ = $(SRC:.c=.o)
OBJ_B = $(SRC_B:.c=.o)
LIB = ar -rcs
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror
NAME = gnl.a
HDR = get_next_line.h
HDRB = get_next_line_bonus.h
%.o: %.c $(HDR) $(HDRB)
	$(CC) -c $(CFLAGS) $< -o $@

all: $(NAME)

$(NAME) : $(OBJ)
	$(LIB) $(NAME) $(OBJ)

bonus: all $(OBJ_B)
	$(LIB) $(NAME) $(OBJ_B)
clean:
	$(RM) $(OBJ) $(OBJ_B)
	
fclean: clean
	$(RM) $(NAME)

re: fclean all
	
.PHONY : clean fclean all