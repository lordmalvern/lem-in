# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bpuschel <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/10/12 16:33:27 by bpuschel          #+#    #+#              #
#    Updated: 2017/10/13 19:29:02 by bpuschel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = lem-in
INCLUDE = includes/
SRC = srcs/
FILES = ant.c bfs.c del.c farm.c htable.c lem_in.c rooms.c queue.c
OBJ = $(FILES:.c=.o)
CC = gcc
CFLAGS = -Wall -Werror -Wextra -I $(INCLUDE) -g -o
LDFLAGS = -Llibft/ 
LDLIBS = -lftprintf
.PHONY: all clean fclean re

all: libftprintf-all $(NAME)

clean: libftprintf-clean
	rm -rf $(OBJ)

fclean: libftprintf-fclean clean
	rm -rf $(NAME)

re: fclean all

$(NAME): $(addprefix $(SRC), $(FILES))
	$(CC) $(CFLAGS) $@ $(LDFLAGS) $(LDLIBS) $^

libftprintf-all:
	cd libft && $(MAKE)

libftprintf-clean:
	cd libft && $(MAKE) clean

libftprintf-fclean:
	cd libft && $(MAKE) fclean

libftprintf-re:
	cd libft && $(MAKE) re
