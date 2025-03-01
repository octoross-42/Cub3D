/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jermarti <jermarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 03:15:49 by jermarti          #+#    #+#             */
/*   Updated: 2025/03/01 05:17:36 by jermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	(void)game;
	return (0);
}

int	key_events(int key, t_map *game)
{
	if (key == 65307 || key == XK_Escape)
		end_game(game);
	else if ((((key == QWERTY_FORWARD) || (key == QWERTY_LEFT)
				|| (key == QWERTY_RIGHT)) && QWERTY_MODE)
		|| (((key == AZERTY_FORWARD) || (key == AZERTY_LEFT)
				|| (key == AZERTY_RIGHT)) && !QWERTY_MODE) || (key == BACKWARD))
		move_player(game, game->player, key);
	else if (key == ROTATE_RIGHT)
		rotate_fov(1, game);
	else if (key == ROTATE_LEFT)
		rotate_fov(-1, game);
	return (0);
}

int	test_fn(int x, int y, t_map *game)
{
	int	i;

	if (x > 1000 || x < 80)
		i = 3;
	else
		i = 2;
	(void)y;
	if ((x < 590 && x > 490) || (game->pos_mouse
			< x + 20 && game->pos_mouse > x - 20))
		return (0);
	if (x > game->pos_mouse)
		rotate_fov(i, game);
	else if (x < game->pos_mouse)
		rotate_fov(i *= -1, game);
	game->pos_mouse = x;
	return (0);
}

int	go_to_mlx_functions(t_map *game)
{
	if (!(init_mlx_struct(game)))
		error_mlx(game);
	if (!change_map_get_player(game))
		error_player(game);
	get_images(game);
	if (!check_images(game))
		exit_images(game);
	game->img = ft_init_image(game->mlx, W_WIDTH, W_HEIGHT);
	if (!(game->img))
		exit_image(game);
	ft_draw(game);
	if (!draw_minimap(game))
		exit_minimap(game);
	mlx_hook(game->mlx->win, KeyPress, KeyPressMask, &key_events, game);
	mlx_hook(game->mlx->win, MotionNotify, PointerMotionMask, &test_fn, game);
	mlx_hook(game->mlx->win, DestroyNotify, ButtonPressMask, &end_game, game);
	mlx_loop(game->mlx->co);
	return (1);
}
