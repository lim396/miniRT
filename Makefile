CC = gcc 
CFLAGS = -Wall -Wextra -Werror -g -I /usr/X11/include
NAME = minirt
LIBFT = ./libft/libft.a
MINILIBX = ./minilibx-linux
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
		atod.c \
		set_utils.c \
		valid_utils.c \
		window_utils.c
OBJS = $(SRCS:.c=.o)
INCLUDE = -I includes -I ./libft/includes


ifeq ($(shell uname), Linux)
	LDFLAGS := -Wl,-start-group -I/usr/X11/include -L/usr/X11/include/../lib -lXext -lX11 -I minilibx-linux -L minilibx-linux -lmlx_Linux
	MINILIBX = ./minilibx-linux/libmlx_Linux.a -Wl,-end-group
else
	LDFLAGS := -I/usr/X11/include -L/usr/X11/include/../lib -lXext -lX11 -I minilibx-linux -L minilibx-linux -lmlx_Darwin
	MINILIBX = ./minilibx-linux/libmlx_Darwin.a
endif


all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ -I minilibx-linux

$(NAME): $(OBJS) $(LIBFT) $(MINILIBX)
	$(CC) $(LDFLAGS) $(INCLUDE) -o $(NAME) $(OBJS) $(LIBFT) $(MINILIBX) 

$(LIBFT):
	$(MAKE) -C ./libft

$(MINILIBX):
	$(MAKE) -C ./minilibx-linux

clean:
	$(MAKE) clean -C ./libft
	$(MAKE) clean -C ./minilibx-linux
	$(RM) *.o

fclean: clean
	$(MAKE) fclean -C ./libft
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
