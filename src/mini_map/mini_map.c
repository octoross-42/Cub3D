/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jermarti <jermarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 03:31:52 by jermarti          #+#    #+#             */
/*   Updated: 2025/03/01 03:32:17 by jermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_and_free_minimap(t_map *game)
{
	if (game->minimap->dot_player)
		mlx_destroy_image(game->mlx->co, game->minimap->dot_player);
	else
		printf("Error, failed to load minimap player texture\n");
	if (game->minimap->empty_square)
		mlx_destroy_image(game->mlx->co, game->minimap->empty_square);
	else
		printf("Error, failed to load minimap empty square texture\n");
	if (game->minimap->wall_square)
		mlx_destroy_image(game->mlx->co, game->minimap->wall_square);
	else
		printf("Error, failed to load minimap wall square texture\n");
	if (game->minimap->void_square)
		mlx_destroy_image(game->mlx->co, game->minimap->void_square);
	else
		printf("Error, failed to load minimap void texture\n");
	if (game->minimap->horizontal_outline)
		mlx_destroy_image(game->mlx->co, game->minimap->horizontal_outline);
	else
		printf("Error, failed to load minimap horizontal outline texture\n");
	if (game->minimap->vertical_outline)
		mlx_destroy_image(game->mlx->co, game->minimap->vertical_outline);
	else
		printf("Error, failed to load minimap vertical ouline texture\n");
}

int	check_minimap_images(t_map *game)
{
	if (!game->minimap->dot_player || !game->minimap->wall_square
		|| !game->minimap->empty_square || !game->minimap->void_square
		|| !game->minimap->horizontal_outline
		|| !game->minimap->vertical_outline)
	{
		check_and_free_minimap(game);
		return (0);
	}
	return (1);
}

void	get_minimap_images(t_map *game)
{
	int	i;
	int	j;
	int	k;
	int	l;
	int	m;

	i = 6;
	j = 6;
	k = 1;
	l = 62;
	m = 122;
	game->minimap->dot_player = mlx_xpm_file_to_image(game->mlx->co,
			"textures/red_dot_player.xpm", &i, &j);
	game->minimap->wall_square = mlx_xpm_file_to_image(game->mlx->co,
			"textures/gray_square.xpm", &i, &j);
	game->minimap->empty_square = mlx_xpm_file_to_image(game->mlx->co,
			"textures/white_square.xpm", &i, &j);
	game->minimap->void_square = mlx_xpm_file_to_image(game->mlx->co,
			"textures/black_square.xpm", &i, &j);
	game->minimap->horizontal_outline = mlx_xpm_file_to_image(game->mlx->co,
			"textures/horiz_outline.xpm", &k, &m);
	game->minimap->vertical_outline = mlx_xpm_file_to_image(game->mlx->co,
			"textures/vertic_outline.xpm", &l, &k);
}

int	get_minimap(t_map *game)
{
	game->minimap = malloc(sizeof(t_minimap));
	if (!game->minimap)
		return (0);
	get_minimap_images(game);
	if (!(check_minimap_images(game)))
	{
		free(game->minimap);
		return (0);
	}
	return (1);
}

int	draw_minimap(t_map *game)
{
	if (!get_minimap(game))
		return (0);
	mlx_put_image_to_window(game->mlx->co, game->mlx->win,
		game->minimap->vertical_outline, 0, 0);
	mlx_put_image_to_window(game->mlx->co, game->mlx->win,
		game->minimap->horizontal_outline, 0, 0);
	mlx_put_image_to_window(game->mlx->co, game->mlx->win,
		game->minimap->vertical_outline, 121, 0);
	mlx_put_image_to_window(game->mlx->co, game->mlx->win,
		game->minimap->horizontal_outline, 0, 61);
	draw_surroundings(game);
	mlx_destroy_image(game->mlx->co, game->minimap->vertical_outline);
	mlx_destroy_image(game->mlx->co, game->minimap->horizontal_outline);
	mlx_put_image_to_window(game->mlx->co, game->mlx->win,
		game->minimap->dot_player, 61, 31);
	return (1);
}
