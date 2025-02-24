NAME = cub3D

SRCS = parsing/exits_copy_map.c \
	utils/gnl/get_next_line_utils.c \
	utils/gnl/get_next_line.c \
	utils/misc.c \
	utils/utils0.c \
	mini_map/mini_map.c \
	mini_map/mini_map_env.c \
	window_handling/mlx_exits.c \
	window_handling/mlx_start.c \
	window_handling/mlx_images.c \
	parsing/parse_file_directions.c \
	parsing/parse_file_floor_and_ceiling.c \
	parsing/parse_file_textures.c \
	parsing/parse_map_content0.c \
	parsing/parse_temp_map0.c \
	parsing/void_fill_temp_map.c \
	rendering/floor_and_ceiling.c \
	rendering/draw.c \
	rendering/walls.c \
	main.c

OBJS = ${SRCS:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror
MLX_FLAGS = -lmlx -lXext -lX11

%.o: %.c
	$(CC) $(CFLAGS) -g3 -Iinclude/ -Imlx -c $< -o ${<:.c=.o}	

$(NAME): ${OBJS}
	$(CC) $(CFLAGS) $(OBJS) -Lmlx -L/usr/lib $(MLX_FLAGS) -lm -o $(NAME)

all : ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all
