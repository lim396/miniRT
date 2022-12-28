CC = gcc
NAME = minirt

SRCS = main.c \
		init.c \
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
		get_shadow_ray.c \
		set_scene.c \
		set_shapes.c \
		vec_operator.c \
		dot_cross_vec.c \
		window_utils.c

OBJS = $(SRCS:.c=.o)
CFLAGS = -g -Werror -Wextra -Wall
INCLUDE = -I includes -I ./libft/includes
LIBFT = libft/libft.a
COPTS = -I /opt/X11/include -L /usr/X11/include/../lib -I minilibx-linux -L minilibx-linux -lm -l Xext -l X11 

UNAME = $(shell uname)
ifeq ($(UNAME), Darwin)
	MLX = minilibx-linux/libmlx_Darwin.a
else ifeq ($(UNAME), Linux)
	MLX = minilibx-linux/libmlx.a
endif

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(MLX) $(COPTS) $(INCLUDE)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ -I minilibx-linux -I /opt/X11/include

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS) $(LIBFT)

$(LIBFT):
	$(MAKE) -C ./libft

clean:
	$(RM) $(OBJS)
	$(MAKE) clean -C ./libft

fclean:
	$(MAKE) fclean -C ./libft

re: fclean all

.PHONY: all clean fclean re
