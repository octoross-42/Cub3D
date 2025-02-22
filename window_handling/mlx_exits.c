#include "cub3D.h"

int end_game(t_map *game)
{
	free_mlx(game);
	final_free(game);
	exit(EXIT_SUCCESS);
}

void	free_images(t_map *game)
{
	mlx_destroy_image(game->mlx->co, game->textures->n_text);
	mlx_destroy_image(game->mlx->co, game->textures->e_text);
	mlx_destroy_image(game->mlx->co, game->textures->s_text);
	mlx_destroy_image(game->mlx->co, game->textures->w_text);
}