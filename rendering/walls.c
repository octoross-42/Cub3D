/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:07:24 by octoross          #+#    #+#             */
/*   Updated: 2025/02/24 07:34:04 by octoross         ###   ########.fr       */
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

void	ft_hit_wall(t_dda *dda, t_map *game)
{
	int		draw_y_start;
	int		draw_y_end;
	float	wall_height;
	t_img	*texture;
	int 	color;
	int		texture_color;
	int	*addr;
	
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
	texture = NULL;
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
	addr = (int *)mlx_get_data_addr(texture->img, &(texture->bpp),
			&(texture->size_line), &(texture->endian));
	// int k = 0;
	// while (k < 36 * 36)
	// {
	// 	printf("%d ", addr[k ++]);
	// }
	(void)texture;
	// printf("direction wall : %c\n", direction);
	int y = draw_y_start;
	texture_color = 0x00FF00;
	int tex_x = 0;
	float wall_x = 0;
	// printf("texture->width : %d\n", texture->width);
	if (dda->side == 1)
	{
		wall_x = (game->player->x + dda->delta_dist_y * dda->ray_dx);
		tex_x = (int)(wall_x * texture->width) % texture->width;

	}
	else
	{
		wall_x = game->player->y + dda->delta_dist_x * dda->ray_dy; // Position x de la collision

		tex_x = (int)(wall_x * texture->width) % texture->width;
	}
	while (y < draw_y_end)
	{
		int tex_y = ((y - draw_y_start) * texture->height) / wall_height;
		// printf("adreesse color : %d\n", tex_y * texture->width + tex_x);
		texture_color = addr[tex_y * texture->width + tex_x];
		// if (texture_color != 0)
			// printf("texture_color : %d\n", texture_color);
		ft_draw_pixel(game->img, dda->x, y, texture_color);
		y ++;
	}
	(void)color;
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
}

void ft_draw_walls(t_map *map)
{
	int 		x;
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