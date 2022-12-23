CC = gcc
NAME = minirt

SRCS = main.c init.c vector_utils.c

OBJS = $(SRCS:.c=.o)
CFLAGS = -g -Werror -Wextra -Wall
INCLUDE = -I includes -I ./libft/includes
LIBFT = libft/libft.a

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS) $(LIBFT)

$(LIBFT):
	$(MAKE) -C ./libft

clean:
	$(MAKE) -C ./libft

fclean:
	$(MAKE) fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
