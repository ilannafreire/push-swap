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
       sort_chunks.c \
       sort_radix.c \
       sort_adaptive.c \
       bench.c \
       utils.c

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
