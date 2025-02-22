#include "cub3D.h"

int	init_mlx_struct(t_map *game)
{
	game->mlx = malloc(sizeof(t_mlx));
	if (!game->mlx)
		return (printf("Error allocing mlx structure\n"), 0);
	game->mlx->co = mlx_init();
	if (!(game->mlx->co))
	{
		free(game->mlx);
		return (printf("Error, mlx connection failed\n"), 0);
	}
	game->mlx->win = mlx_new_window(game->mlx->co, W_WIDTH, W_HEIGHT, "cub3D");
	if (!(game->mlx->win))
	{
		mlx_destroy_display(game->mlx->co);
		free(game->mlx->co);
		free(game->mlx);
		return (printf("Error, mlx failed to open a window\n"), 0);
	}
	return (printf("connected to mlx properly\n"), 1);
}

int	key_events(int key, t_map *game)
{
	if (key == 65307 || key == XK_Escape)
		end_game(game);
	/*
	left arrow == 65361 => look left;
	right arrow == 65363 => look right;
	a == 97;
	w == 119;
	d == 100;
	s == 115;
	*/
	else if (key == 97)
		mlx_put_image_to_window(game->mlx->co, game->mlx->win,
		game->textures->w_text,	0, 640/2);
	else if (key == 119)
		mlx_put_image_to_window(game->mlx->co, game->mlx->win,
		game->textures->n_text,	1080/2, 0);
	else if (key == 100)
		mlx_put_image_to_window(game->mlx->co, game->mlx->win,
		game->textures->e_text,	1080/2, 640-36);
	else if (key == 115)
		mlx_put_image_to_window(game->mlx->co, game->mlx->win,
		game->textures->s_text,	1080-36, 640/2);
	return (0);
}

int	go_to_mlx_functions(t_map *game)
{
	if (!(init_mlx_struct(game)))
		return (0);

	change_map_get_player(game);
	get_images(game);
	if (!check_images(game))
		return (0);
	mlx_key_hook(game->mlx->win, &key_events, game);
	mlx_hook(game->mlx->win, KeyRelease, KeyReleaseMask,
		&key_events, game);
	mlx_hook(game->mlx->win, DestroyNotify,
		ButtonPressMask, &end_game, game);
	mlx_loop(game->mlx->co);
	return (1);
}