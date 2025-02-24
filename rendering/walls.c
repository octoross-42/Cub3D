/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:07:24 by octoross          #+#    #+#             */
/*   Updated: 2025/02/24 05:48:21 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	ft_abs(float n)
{
	if (n < 0)
		return (-n);
	return (n);
}

void	ft_init_dda(t_dda *dda, t_map *game)
{
	printf("here\n");
	if (dda->ray_dx == 0)
		dda->delta_dist_x = FLT_MAX;
	else
		dda->delta_dist_x = ft_abs(1 / dda->ray_dx);
	if (dda->ray_dy == 0)
		dda->delta_dist_y = FLT_MAX;
	else
		dda->delta_dist_y = ft_abs(1 / dda->ray_dy);
	dda->hit = 0;
	
	printf("djsfk\n");
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
	printf("qsjdqmsazhere\n");
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

void	ft_hit_wall(t_dda *dda, t_map *game)
{
	int		draw_y_start;
	int		draw_y_end;
	float	wall_height;
	t_img	*texture;
	
	dda->hit = 1;
	if (dda->side == 0)
		dda->wall_dist = dda->side_dist_x - dda->delta_dist_x;
	else
		dda->wall_dist = dda->side_dist_y - dda->delta_dist_y;
	printf("la\n");
	wall_height = (int)(W_HEIGHT / dda->wall_dist);
	draw_y_start = -(wall_height / 2) + (W_HEIGHT / 2);
	if(draw_y_start < 0)
		draw_y_start = 0;
	draw_y_end = (wall_height / 2) + (W_HEIGHT / 2);
	if(draw_y_end >= W_HEIGHT)
	draw_y_end = W_HEIGHT - 1;
	texture = NULL;
	printf("lna\n");
	if (dda->side == 0)
	{
		if (dda->ray_dx > game->player->x)
			texture = &(game->textures->w_text);
		else
			texture = &(game->textures->e_text);
	}
	else
	{
		if (dda->ray_dy > game->player->y)
		texture = &(game->textures->n_text);
		else
		texture = &(game->textures->s_text);
	}
	printf("ladqsa\n");
	texture->addr = mlx_get_data_addr(texture->img, &(texture->bpp),
			&(texture->size_line), &(texture->endian));
	(void)texture;
	// printf("direction wall : %c\n", direction);
	int y = draw_y_start;
	while (y < draw_y_end)
	{
		ft_draw_pixel(game->img, dda->x, y, 0x00FF00);
		y ++;
	}
}

void	ft_dda(t_dda *dda, t_map *game)
{
	ft_init_dda(dda, game);
	while (dda->hit == 0 && (dda->map_i > 0) && (dda->map_j > 0) && (dda->map_i < W_HEIGHT - 1) && (dda->map_j < W_HEIGHT - 1))
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
        if (game->map[dda->map_j][dda->map_i] == '1')
			ft_hit_wall(dda, game);
    }
	if (dda->hit == 0)
		printf("no wall\n");
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
		dda.x = x;
		dda.fov_x = 2 * x / (double)W_WIDTH - 1;
		printf("player x : %f\n", player->dx);
		printf("camera plane x : %f\n", player->camera_plane_dx);
		dda.ray_dx = player->dx + player->camera_plane_dx * dda.fov_x;
		dda.ray_dy = player->dy + player->camera_plane_dy * dda.fov_x;
		dda.map_i = (int)player->x;
		dda.map_j = (int)player->y;
		ft_dda(&dda, map);
		x ++;
	}
}