/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jermarti <jermarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 03:32:42 by jermarti          #+#    #+#             */
/*   Updated: 2025/03/01 03:32:49 by jermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	deal_with_minimap(t_map *game)
{
	if (game->minimap->dot_player)
		mlx_destroy_image(game->mlx->co, game->minimap->dot_player);
	if (game->minimap->wall_square)
		mlx_destroy_image(game->mlx->co, game->minimap->wall_square);
	if (game->minimap->empty_square)
		mlx_destroy_image(game->mlx->co, game->minimap->empty_square);
	if (game->minimap->void_square)
		mlx_destroy_image(game->mlx->co, game->minimap->void_square);
	free(game->minimap);
}
