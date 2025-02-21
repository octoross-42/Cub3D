#include "cub3D.h"

int end_game(t_map *game)
{
	free_mlx(game);
	final_free(game);
	exit(EXIT_SUCCESS);
}