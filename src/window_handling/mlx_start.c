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
	else if ((((key == QWERTY_FORWARD) || (key == QWERTY_LEFT) || (key == QWERTY_RIGHT)) && QWERTY_MODE)
		|| (((key == AZERTY_FORWARD) || (key == AZERTY_LEFT) || (key == AZERTY_RIGHT)) && !QWERTY_MODE) || (key == BACKWARD))
		move_player(game, game->player, key);
	else if (key == ROTATE_RIGHT)
		rotate_fov(game, 1);
	else if (key == ROTATE_LEFT)
		rotate_fov(game, -1);
	return (0);
}

int	test_fn(int x, int y, t_map *game)
{
	// printf("%i %i\n", x, y);
	(void)game;
	(void)x;
	(void)y;
	return (0);
}

int mouse_events(int button, t_map *game)
{
	if (button == 1)
		printf("mouse left click detected\n");
	(void)game;
	return (0);
}

int	go_to_mlx_functions(t_map *game)
{
	if (!(init_mlx_struct(game)))
		return (0);

	if (!change_map_get_player(game))
		return (0);
	get_images(game);
	if (!check_images(game))
		return (0);
	
	game->img = ft_init_image(game->mlx, W_WIDTH, W_HEIGHT);
	if (!(game->img))
		return (0);
	ft_draw(game);
	if (!draw_minimap(game))
		return (0);
	
	// mlx_do_key_autorepeaton(game->mlx->co);
	// mlx_key_hook(game->mlx->win, &key_events, game);
	mlx_mouse_hook(game->mlx->win, &mouse_events, game);
	mlx_hook(game->mlx->win, KeyPress, KeyPressMask, &key_events, game);
	// mlx_hook(game->mlx->win, ButtonPress, ButtonPressMask, &rotate_fov, game);
	mlx_hook(game->mlx->win, MotionNotify, PointerMotionMask, &test_fn, game);//tracks the mouse
	mlx_hook(game->mlx->win, DestroyNotify, ButtonPressMask, &end_game, game);
	mlx_loop(game->mlx->co);
	return (1);
}