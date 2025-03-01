/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jermarti <jermarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 03:30:24 by jermarti          #+#    #+#             */
/*   Updated: 2025/03/01 03:30:25 by jermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*int_tab_to_hexa(int *lul)
{
	char	*rgb;

	rgb = malloc(7);
	if (!(rgb))
		return (NULL);
	rgb[0] = HEXA[lul[0] / 16];
	rgb[1] = HEXA[lul[0] % 16];
	rgb[2] = HEXA[lul[1] / 16];
	rgb[3] = HEXA[lul[1] % 16];
	rgb[4] = HEXA[lul[2] / 16];
	rgb[5] = HEXA[lul[2] % 16];
	rgb[6] = 0;
	return (rgb);
}

void	draw_that_fk_image(t_map *game, int i, int j)
{
	int	x;
	int	y;

	x = game->player->y + i;
	y = game->player->x + j;
	if (x < 0 || y < 0 || x > game->num_lines - 1)
		mlx_put_image_to_window(game->mlx->co, game->mlx->win,
			game->minimap->void_square, 61 + (j * 6),
			31 + (i * 6));
	else if (y > ft_len(game->map[x]) - 1)
		mlx_put_image_to_window(game->mlx->co, game->mlx->win,
			game->minimap->void_square, 61 + (j * 6),
			31 + (i * 6));
	else if (game->map[x][y] == '\n')
		mlx_put_image_to_window(game->mlx->co, game->mlx->win,
			game->minimap->void_square, 61 + (j * 6),
			31 + (i * 6));
	else if (game->map[x][y] == '1')
		mlx_put_image_to_window(game->mlx->co, game->mlx->win,
			game->minimap->wall_square, 61 + (j * 6),
			31 + (i * 6));
	else
		mlx_put_image_to_window(game->mlx->co, game->mlx->win,
			game->minimap->empty_square, 61 + (j * 6),
			31 + (i * 6));
}

void	draw_surroundings(t_map *game)
{
	int	i;
	int	j;

	i = -10;
	j = -5;
	while (i < 10)
	{
		while (j < 5)
		{
			draw_that_fk_image(game, j, i);
			j ++;
		}
		j = -5;
		i ++;
	}
}

void	refresh_minimap(t_map *game)
{
	int	i;
	int	j;

	i = -10;
	j = -5;
	while (i < 10)
	{
		while (j < 5)
		{
			draw_that_fk_image(game, j, i);
			j ++;
		}
		j = -5;
		i ++;
	}
	mlx_put_image_to_window(game->mlx->co, game->mlx->win,
		game->minimap->dot_player, 61, 31);
}
