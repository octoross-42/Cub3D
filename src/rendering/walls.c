/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:07:24 by octoross          #+#    #+#             */
/*   Updated: 2025/02/24 12:07:21 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_draw_walls(t_map *map)
{
	int			x;
	t_player	*player;
	t_dda		dda;

	player = map->player;
	x = 0;
	while (x < W_WIDTH)
	{
		dda.x = x;
		dda.fov_x = 2.0 * x / (double)W_WIDTH - 1.0;
		dda.ray_dx = player->dx + player->camera_plane_dx * dda.fov_x;
		dda.ray_dy = player->dy + player->camera_plane_dy * dda.fov_x;
		dda.map_i = (int)player->x;
		dda.map_j = (int)player->y;
		ft_dda(&dda, map);
		x ++;
	}
}
