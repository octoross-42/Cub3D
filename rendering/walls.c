/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:07:24 by octoross          #+#    #+#             */
/*   Updated: 2025/02/24 03:28:09 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ft_abs(float n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	ft_init_dda(t_dda *dda, t_map *game)
{
	if (dda->ray_dx == 0)
		dda->delta_dist_x = FLT_MAX;
	else
		dda->delta_dist_x = ft_abs(1 / dda->ray_dx);
	if (dda->ray_dy == 0)
		dda->delta_dist_y = FLT_MAX;
	else
		dda->delta_dist_y = ft_abs(1 / dda->ray_dy);
	dda->hit = 0;
	if (dda->ray_dx < 0)
	{
	  dda->step_x = -1;
	  dda->side_dist_x = (game->player->x - dda->map_i) * dda->delta_dist_x;
	}
	else
	{
	  dda->step_x = 1;
	  dda->side_dist_x = (dda->map_i + 1.0 - game->player->x) * dda->delta_dist_x;
	}
	if (dda->ray_dy < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (game->player->y - dda->map_j) * dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_j + 1.0 - game->player->y) * dda->delta_dist_y;
	}
}

void	ft_draw_vertical_line(t_map *game)
{
	(void)game;
	
}

void	ft_hit_wall(t_dda *dda, t_map *game)
{
	int		draw_y_start;
	int		draw_y_end;
	char 	direction;
	float	wall_height;
	
	dda->hit = 1;
	if (dda->side == 0)
		dda->wall_dist = dda->side_dist_x - dda->delta_dist_x;
	else
		dda->wall_dist = dda->side_dist_y - dda->delta_dist_y;
	wall_height = (int)(W_HEIGHT / dda->wall_dist);
	draw_y_start = -(wall_height / 2) + (W_HEIGHT / 2);
	if(draw_y_start < 0)
		draw_y_start = 0;
	draw_y_end = (wall_height / 2) + (W_HEIGHT / 2);
	if(draw_y_end >= W_HEIGHT)
	draw_y_end = W_HEIGHT - 1;
	if (dda->side == 0)
	{
		if (dda->ray_dx > game->player->x)
			direction = 'W';
		else
			direction = 'E';
	}
	else
	{
		if (dda->ray_dy > game->player->y)
			direction = 'N';
		else
			direction = 'S';
	}
	(void)direction;
	// printf("direction wall : %c\n", direction);

}

void	ft_dda(t_dda *dda, t_map *game)
{
	ft_init_dda(dda, game);
	while (dda->hit == 0)
    {
        if (dda->side_dist_x < dda->side_dist_y)
        {
			dda->side_dist_x += dda->delta_dist_x;
			dda->map_i += dda->step_x;
			dda->side = 0;
        }
        else
        {
			dda->side_dist_y += dda->delta_dist_y;
			dda->map_j += dda->step_y;
         	dda->side = 1;
        }
		// printf("map_i : %d, map_j : %d\n", dda->map_i, dda->map_j);
        if (game->map[dda->map_j][dda->map_i] == '1')
			ft_hit_wall(dda, game);
    }
}

void ft_draw_walls(t_map *map)
{
	int 		x;
	t_player	*player;
	t_dda		dda;

	player = map->player;
	x = 0;
	while (map->map[x])
	{
		int j = 0;
		while (map->map[x][j])
			printf("%c", map->map[x][j ++]);
		printf("\t%d %d\n", x, j);
		x ++;
	}
	x = 0;
	while (x < W_WIDTH)
	{
		dda.fov_x = 2 * x / (double)W_WIDTH - 1;
		dda.ray_dx = player->dx + player->camera_plane_dx * dda.fov_x;
		dda.ray_dy = player->dy + player->camera_plane_dy * dda.fov_x;
		dda.map_i = (int)player->x;
		dda.map_j = (int)player->y;
		ft_dda(&dda, map);
		x ++;
	}
}