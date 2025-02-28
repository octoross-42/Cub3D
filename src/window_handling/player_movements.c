#include "cub3D.h"

void	move_player(t_map *game, t_player *player, int key)
{
	float	move_x;
	float	move_y;

	move_x = 0;
	move_y = 0;
	if (((key == QWERTY_RIGHT) && QWERTY_MODE) || ((key == AZERTY_RIGHT) && !QWERTY_MODE))
	{
		move_x = -player->dy * SPEED;
		move_y = player->dx * SPEED;
	}
	else if (((key == QWERTY_LEFT) && QWERTY_MODE) || ((key == AZERTY_LEFT) && !QWERTY_MODE))
	{
		move_x = player->dy * SPEED;
		move_y = -player->dx * SPEED;
	}
	else if (((key == QWERTY_FORWARD) && QWERTY_MODE) || ((key == AZERTY_FORWARD) && !QWERTY_MODE))
	{
		move_x = player->dx * SPEED;
		move_y = player->dy * SPEED;
	}
	else if (key == BACKWARD)
	{
		move_x = -player->dx * SPEED;
		move_y = -player->dy * SPEED;
	}
	else
		return ;
	if ((game->map[(int)player->y][(int)(player->x + move_x)] != '1')
		&& (game->map[(int)(player->y + move_y)][(int)player->x] != '1'))
	{
		player->x += move_x;
		player->y += move_y;
		ft_draw(game);
		refresh_minimap(game);
	}
	else
		printf("player can't be moved due to a wall or map boundary\n OR because it's close to a wall\n");
}

void	rotate_fov(t_map *game, int right)
{
	float	old_dx;
	float	old_camera_plane_dx;
	float	rotation;

	rotation = ROTATION * (2 * right - 1);
	old_dx = game->player->dx;
	old_camera_plane_dx = game->player->camera_plane_dx;
	game->player->dx = game->player->dx * cos(rotation) - game->player->dy * sin(rotation);
	game->player->dy = old_dx * sin(rotation) + game->player->dy * cos(rotation);
	game->player->camera_plane_dx = game->player->camera_plane_dx * cos(rotation) - game->player->camera_plane_dy * sin(rotation);
	game->player->camera_plane_dy = old_camera_plane_dx * sin(rotation) + game->player->camera_plane_dy * cos(rotation);
	ft_draw(game);
	refresh_minimap(game);
}