NAME	= cub3D
CC	= cc
CFLAGS  = -Wall -Wextra -Werror -I includes -I mlx_src
RM	= rm -f


LIBFT	= libft/libft.a
MLX_DIR = mlx_src
MLX_FLAGS = -L $(MLX_DIR) -lmlx -lX11 -lXext -lm

SRCS	= main.c \
			mlx/textures.c \
			mlx/mlx_init.c \
			mlx/mlx_hooks.c \
			mlx/mlx_render.c \
			mlx/mlx_events.c \
			mlx/move.c \
			parsing/parser.c \
			parsing/parser_path.c \
			parsing/parser_map.c \
			parsing/check.c \
			parsing/check_map.c \
			parsing/init.c \
			parsing/init_player.c \
			raycasting/raycast.c \
			raycasting/init_ray.c \
			raycasting/dda.c \
			raycasting/render.c \
			raycasting/drawall.c \
			utils/error.c \
			utils/utils.c \
			gnl/get_next_line.c \
			gnl/get_next_line_utils.c

OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(MAKE) -C $(MLX_DIR)
	$(CC) $(CFLAGS) $(OBJS) -L libft -lft $(MLX_FLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	$(MAKE) -C libft

clean:
	$(RM) $(OBJS)
	$(MAKE) -C libft clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all clean fclean re
