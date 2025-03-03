NAME = cub3D

RESET	:=	\e[0m
BOLD	:=	\e[1m
ITAL	:=	\e[3m
BLINK	:=	\e[5m
GREEN	:=	\e[32m
YELLOW	:=	\e[33m
BLUE	:=	\e[34m
CYAN	:=	\e[36m
PINK	:=	\e[38;2;255;182;193m


SRCS = src/utils/gnl/get_next_line_utils.c \
	src/utils/gnl/get_next_line.c \
	src/utils/misc.c \
	src/utils/utils0.c \
	src/mini_map/free_mini_map.c \
	src/mini_map/mini_map.c \
	src/mini_map/mini_map_env.c \
	src/window_handling/mlx_exits.c \
	src/window_handling/mlx_exits1.c \
	src/window_handling/mlx_start.c \
	src/window_handling/mlx_images.c \
	src/window_handling/player_movements.c \
	src/parsing/parse_file_directions.c \
	src/parsing/parse_file_floor_and_ceiling.c \
	src/parsing/parse_file_floor_and_ceiling1.c \
	src/parsing/parse_file_textures.c \
	src/parsing/parse_map_content0.c \
	src/parsing/parse_temp_map0.c \
	src/parsing/void_fill_temp_map.c \
	src/parsing/exits_copy_map.c \
	src/rendering/floor_and_ceiling.c \
	src/rendering/draw.c \
	src/rendering/walls.c \
	src/rendering/dda.c \
	src/main.c

OBJS = ${SRCS:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -lmlx -lXext -lX11

MLX_DIR = mlx
MLX_REPO = https://github.com/42paris/minilibx-linux.git

%.o: %.c
	$(CC) $(CFLAGS) -g3 -Iinclude/ -Imlx -c $< -o ${<:.c=.o}	

$(NAME): ${OBJS}
	$(CC) $(CFLAGS) $(OBJS) -Lmlx -L/usr/lib $(MLX_FLAGS) -lm -lz -o $(NAME)

all : mlx ${NAME}

mlx :
	if [ ! -d "$(MLX_DIR)" ]; then \
		git clone $(MLX_REPO) $(MLX_DIR) && cd $(MLX_DIR) && ./configure && cd ../; \
		fi


clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all
