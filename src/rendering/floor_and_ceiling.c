/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floor_and_ceiling.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 01:07:34 by octoross          #+#    #+#             */
/*   Updated: 2025/02/25 03:18:48 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


// TODO: ajouter optimisation pour zoom (on voit moins donc moins de calcul)

// TODO ajouter couleurs plafonds et sols de la map

void	ft_draw_floor_and_ceiling(t_map *game)
{
	int	i;
	int	j;

	
	i = 0;
	while (i < W_WIDTH)
	{
		j = 0;
		while (j < W_HEIGHT)
		{
			if (j < W_HEIGHT / 2)
				ft_draw_pixel(game->img, i, j, 0x000000);
			else
				ft_draw_pixel(game->img, i, j, 0x252525);
			j++;
		}
		i++;
	}
}
