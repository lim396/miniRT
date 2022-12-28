CC = gcc
NAME = minirt

SRCS = main.c init.c \
		vector_utils.c \
		camera_ray.c \
		equation.c \
		is_hittable.c \
		luminance.c \
		draw.c \
		ray_trace.c \
		color_utils.c \
		utils.c \
		get_nearest.c \
		get_shadow_ray.c

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
	$(RM) $(OBJS)
	$(MAKE) -C ./libft

fclean:
	$(MAKE) fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
