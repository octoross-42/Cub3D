#include "cub3D.h"

void	release_textures(t_map *game)
{
	free(game->textures->n_path);
	free(game->textures->s_path);
	free(game->textures->e_path);
	free(game->textures->w_path);
	free(game->textures->ceiling);
	free(game->textures->floor);
	free(game->textures);
}

void	final_free(t_map *game)
{
	free(game->player);
	release_textures(game);
	free_map(game->map);
}

void	free_mlx(t_map *game)
{
	mlx_destroy_window(game->mlx->co, game->mlx->win);
	mlx_destroy_display(game->mlx->co);
	free(game->mlx->co);
	free(game->mlx);
}

void	free_images(t_map *game)
{
	mlx_destroy_image(game->mlx->co, game->textures->n_text);
	mlx_destroy_image(game->mlx->co, game->textures->e_text);
	mlx_destroy_image(game->mlx->co, game->textures->s_text);
	mlx_destroy_image(game->mlx->co, game->textures->w_text);
	mlx_destroy_image(game->mlx->co, game->img->img);
	free(game->img);
}

int end_game(t_map *game)
{
	free_images(game);
	final_free(game);
	free_mlx(game);
	free(game);
	exit(EXIT_SUCCESS);
}
