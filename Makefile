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

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDE = include

MLX_DIR = mlx
MLX_REPO = https://github.com/42paris/minilibx-linux.git


MINIMAP_SRCS = src/mini_map/free_mini_map.c \
				src/mini_map/mini_map_env.c \
				src/mini_map/mini_map.c
PARSING_SRCS = src/parsing/parse_file_directions.c \
				src/parsing/parse_file_floor_and_ceiling.c \
				src/parsing/parse_file_floor_and_ceiling1.c \
				src/parsing/parse_file_textures.c \
				src/parsing/parse_map_content0.c \
				src/parsing/parse_temp_map0.c \
				src/parsing/void_fill_temp_map.c \
				src/parsing/exits_copy_map.c
RENDERING_SRCS = src/rendering/floor_and_ceiling.c \
				src/rendering/draw.c \
				src/rendering/walls.c \
				src/rendering/dda.c
UTILS_SRCS = src/utils/gnl/get_next_line_utils.c \
				src/utils/gnl/get_next_line.c \
				src/utils/misc.c \
				src/utils/utils0.c
WINDOW_HANDLING = src/window_handling/mlx_exits.c \
				src/window_handling/mlx_exits1.c \
				src/window_handling/mlx_start.c \
				src/window_handling/mlx_images.c \
				src/window_handling/player_movements.c
MAIN_SRCS = src/main.c


SRCS = $(MINIMAP_SRCS) \
	$(PARSING_SRCS) \
	$(RENDERING_SRCS) \
	$(UTILS_SRCS) \
	$(WINDOW_HANDLING) \
	$(MAIN_SRCS)

OBJS_DIR = objs
OBJS = $(SRCS:%.c=$(OBJS_DIR)/%.o)

all: mlx $(NAME)

mlx_config :
	@printf "$(BOLD)$(BLUE)[mlx] $(RESET)Configuring mlx...\n\n"
	@git clone $(MLX_REPO) $(MLX_DIR) && \
	cd $(MLX_DIR) && \
	./configure && \
	cd ../
	@printf "$(BOLD)$(BLUE)[mlx] $(RESET)Configuring mlx completed !\n\n"

mlx :
	@if [ ! -d "$(MLX_DIR)" ]; then \
		$(MAKE) --silent mlx_config; \
	fi

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: %.c | $(OBJS_DIR)
	@mkdir -p $(dir $@)
	@printf "\r                                                                                                                                       \r\
	$(BOLD)$(BLUE)[objs]: $(RESET)$<"
	@$(CC) $(CFLAGS) -I$(INCLUDE) -Imlx -g3 -c $< -o $@

$(NAME): $(OBJS)
	@printf "\r                                                                                                                                       \r\
	$(BOLD)$(BLUE)Compilation: $(RESET)done!\n"
	@printf "$(BOLD)$(YELLOW)\nLinking...$(RESET)\n"
	@$(CC) $(CFLAGS) $(OBJS) -Lmlx -L/usr/lib -lmlx -lXext -lX11 -lm -lz -o $(NAME)
	@printf "$(BOLD)$(BLUE)Linking: $(RESET)done!$(RESET)\n"
	@printf "\n$(BOLD)$(GREEN)[$(NAME) ready]$(RESET)\n"

clean:
	@rm -rf $(OBJS_DIR)
	@printf "$(BOLD)$(CYAN)[objs]\t $(RESET)Clean completed\n"
 
fclean: 
	@rm -rf $(OBJS_DIR)
	@rm -rf $(NAME)
	@printf "$(BOLD)$(CYAN)[objs/cub3D] $(RESET)Full clean completed!\n"

re:	
	@make --silent mlx
	@make --silent fclean
	@printf "\n"
	@make --silent $(NAME)

.PHONY:	all clean fclean re