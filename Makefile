# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ifreire <ifreire@student.42sp.org.br>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/07/05 14:00:00 by ifreire           #+#    #+#              #
#    Updated: 2026/07/14 23:43:32 by ifreire          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRCS = main.c \
       parse.c \
       stack.c \
       stack_utils.c \
       ops_a.c \
       ops_b.c \
       ops_double.c \
       disorder.c \
       sort_selection.c \
       sort_small.c \
       sort_chunks_utils.c \
       sort_chunks.c \
       sort_radix.c \
       sort_adaptive.c \
       bench.c \
       parse_utils.c \
       io_utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c push_swap.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
