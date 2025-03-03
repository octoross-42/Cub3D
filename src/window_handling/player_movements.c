/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movements.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 03:08:27 by jermarti          #+#    #+#             */
/*   Updated: 2025/03/03 19:09:19 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	new_player_coords(float *x, float *y, t_player *player, int key)
{
	if (((key == QWERTY_RIGHT) && QWERTY_MODE)
		|| ((key == AZERTY_RIGHT) && !QWERTY_MODE))
		return (*x = -player->dy * SPEED,
			*y = player->dx * SPEED, 1);
	else if (((key == QWERTY_LEFT) && QWERTY_MODE)
		|| ((key == AZERTY_LEFT) && !QWERTY_MODE))
		return (*x = player->dy * SPEED,
			*y = -player->dx * SPEED, 1);
	else if (((key == QWERTY_FORWARD) && QWERTY_MODE)
		|| ((key == AZERTY_FORWARD) && !QWERTY_MODE))
		return (*x = player->dx * SPEED,
			*y = player->dy * SPEED, 1);
	else if (key == BACKWARD)
		return (*x = -player->dx * SPEED,
			*y = -player->dy * SPEED, 1);
	return (0);
}

void	move_player(t_map *game, t_player *player, int key)
{
	float	move_x;
	float	move_y;

	move_x = 0;
	move_y = 0;
	if (!new_player_coords(&move_x, &move_y, player, key))
		return ;
	if ((game->map[(int)player->y][(int)(player->x + move_x)] != '1')
		&& (game->map[(int)(player->y + move_y)][(int)player->x] != '1'))
	{
		player->x += move_x;
		player->y += move_y;
		ft_draw(game);
		refresh_minimap(game);
	}
}

int	rotate_fov(int r_dir, t_map *game)
{
	float	old_dx;
	float	old_camera_plane_dx;
	float	rotation;

	rotation = ROTATION * (float) r_dir;
	old_dx = game->player->dx;
	old_camera_plane_dx = game->player->camera_plane_dx;
	game->player->dx = game->player->dx
		* cos(rotation) - game->player->dy * sin(rotation);
	game->player->dy = old_dx * sin(rotation) + game->player->dy
		* cos(rotation);
	game->player->camera_plane_dx = game->player->camera_plane_dx
		* cos(rotation) - game->player->camera_plane_dy * sin(rotation);
	game->player->camera_plane_dy = old_camera_plane_dx * sin(rotation)
		+ game->player->camera_plane_dy * cos(rotation);
	ft_draw(game);
	refresh_minimap(game);
	return (0);
}
