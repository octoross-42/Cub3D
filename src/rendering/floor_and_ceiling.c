/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jermarti <jermarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 01:07:34 by octoross          #+#    #+#             */
/*   Updated: 2025/03/01 03:24:07 by jermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// TODO: ajouter optimisation pour zoom (on voit moins donc moins de calcul)

// TODO ajouter couleurs plafonds et sols de la map

void	ft_draw_floor_and_ceiling(t_map *game)
{
	int	i;
	int	j;
	int	floor_color;
	int	ceiling_color;

	i = 0;
	floor_color = (game->textures->f_col[0] << 16)
		| (game->textures->f_col[1] << 8) | game->textures->f_col[2];
	ceiling_color = (game->textures->c_col[0] << 16)
		| (game->textures->c_col[1] << 8) | game->textures->c_col[2];
	while (i < W_WIDTH)
	{
		j = 0;
		while (j < W_HEIGHT)
		{
			if (j < W_HEIGHT / 2)
				ft_draw_pixel(game->img, i, j, ceiling_color);
			else
				ft_draw_pixel(game->img, i, j, floor_color);
			j++;
		}
		i++;
	}
}
