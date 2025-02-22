#include "cub3D.h"

void	check_and_free(t_map *game)
{
	if (game->textures->n_text)
		mlx_destroy_image(game->mlx->co, game->textures->n_text);
	else
		printf("Error, failed to load north texture\n");
	if (game->textures->s_text)
		mlx_destroy_image(game->mlx->co, game->textures->s_text);
	else
		printf("Error, failed to load south texture\n");
	if (game->textures->e_text)
		mlx_destroy_image(game->mlx->co, game->textures->e_text);
	else
		printf("Error, failed to load east texture\n");
	if (game->textures->w_text)
		mlx_destroy_image(game->mlx->co, game->textures->w_text);
	else
		printf("Error, failed to load west texture\n");
}

int	check_images(t_map *game)
{
	if (!game->textures->n_text || !game->textures->e_text
        || !game->textures->w_text ||!game->textures->s_text)
	{
		check_and_free(game);
        return (0);
	}
    return (1);
}

void	get_images(t_map *game)
{
	int	i;
	int	j;

	i = 36;
	j = 36;
	game->textures->n_text = mlx_xpm_file_to_image(game->mlx->co,
		game->textures->n_path, &i, &j);
	game->textures->e_text = mlx_xpm_file_to_image(game->mlx->co,
		game->textures->e_path, &i, &j);
	game->textures->s_text = mlx_xpm_file_to_image(game->mlx->co,
		game->textures->s_path, &i, &j);
	game->textures->w_text = mlx_xpm_file_to_image(game->mlx->co,
		game->textures->w_path, &i, &j);
}