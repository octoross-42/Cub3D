#include "cub3D.h"

void	check_and_free(t_map *game)
{
	if (game->textures->n_text.img)
		mlx_destroy_image(game->mlx->co, game->textures->n_text.img);
	else
		printf("Error, failed to load north texture\n");
	if (game->textures->s_text.img)
		mlx_destroy_image(game->mlx->co, game->textures->s_text.img);
	else
		printf("Error, failed to load south texture\n");
	if (game->textures->e_text.img)
		mlx_destroy_image(game->mlx->co, game->textures->e_text.img);
	else
		printf("Error, failed to load east texture\n");
	if (game->textures->w_text.img)
		mlx_destroy_image(game->mlx->co, game->textures->w_text.img);
	else
		printf("Error, failed to load west texture\n");
}

int	check_images(t_map *game)
{
	if (!game->textures->n_text.img || !game->textures->e_text.img
        || !game->textures->w_text.img ||!game->textures->s_text.img)
	{
		check_and_free(game);
        return (0);
	}
    return (1);
}

void	get_images(t_map *game)
{
	t_paths	*t;

	t = game->textures;
	t->n_text.img = mlx_xpm_file_to_image(game->mlx->co,
		t->n_path, &t->n_text.width, &t->n_text.height);
	printf("n_path : %s\n", t->n_path);
	t->s_text.img = mlx_xpm_file_to_image(game->mlx->co,
		t->s_path, &t->s_text.width, &t->s_text.height);
		printf("s_path : %s\n", t->s_path);
	t->e_text.img = mlx_xpm_file_to_image(game->mlx->co,
		t->e_path, &t->e_text.width, &t->e_text.height);
		printf("e_path : %s\n", t->e_path);
	t->w_text.img = mlx_xpm_file_to_image(game->mlx->co,
		t->w_path, &t->w_text.width, &t->w_text.height);
		printf("w_path : %s\n", t->w_path);
}