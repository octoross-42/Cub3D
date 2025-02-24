/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:51:45 by octoross          #+#    #+#             */
/*   Updated: 2025/02/24 11:51:45 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_init_dda_steps(t_dda *dda, t_map *game)
{
	if (dda->ray_dx < 0)
	{
		dda->step_x = -1;
		dda->side_dist_x = (game->player->x - dda->map_i)
			* dda->delta_dist_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_dist_x = (dda->map_i + 1.0 - game->player->x)
			* dda->delta_dist_x;
	}
	if (dda->ray_dy < 0)
	{
		dda->step_y = -1;
		dda->side_dist_y = (game->player->y - dda->map_j)
			* dda->delta_dist_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_dist_y = (dda->map_j + 1.0 - game->player->y)
			* dda->delta_dist_y;
	}
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
	ft_init_dda_steps(dda, game);
}

void	ft_calculate_wall(t_dda *dda, t_map *game)
{
	if (dda->side == 0)
		dda->wall_dist = dda->side_dist_x - dda->delta_dist_x;
	else
		dda->wall_dist = dda->side_dist_y - dda->delta_dist_y;
	dda->wall_height = (int)(W_HEIGHT / dda->wall_dist);
	if (dda->side == 0)
	{
		dda->wall_x = game->player->y + dda->wall_dist * dda->ray_dy;
		if (dda->ray_dx > 0)
			dda->texture = &(game->textures->w_text);
		else
			dda->texture = &(game->textures->e_text);
	}
	else
	{
		dda->wall_x = game->player->x + dda->wall_dist * dda->ray_dx;
		if (dda->ray_dy > 0)
			dda->texture = &(game->textures->n_text);
		else
			dda->texture = &(game->textures->s_text);
	}
}

void	ft_hit_wall(t_dda *dda, t_map *game)
{
	int		color;
	int		*addr;
	int		y;
	int		x_text;
	int		y_text;

	dda->hit = 1;
	ft_calculate_wall(dda, game);
	addr = (int *)mlx_get_data_addr(dda->texture->img, &(dda->texture->bpp),
			&(dda->texture->size_line), &(dda->texture->endian));
	x_text = (int)(dda->wall_x * dda->texture->width) % dda->texture->width;
	dda->draw_y_start = -(dda->wall_height / 2) + (W_HEIGHT / 2);
	if (dda->draw_y_start < 0)
		dda->draw_y_start = 0;
	dda->draw_y_end = (dda->wall_height / 2) + (W_HEIGHT / 2);
	if (dda->draw_y_end >= W_HEIGHT)
		dda->draw_y_end = W_HEIGHT - 1;
	y = dda->draw_y_start;
	while (y < dda->draw_y_end)
	{
		y_text = ((y - dda->draw_y_start)
				* dda->texture->height) / dda->wall_height;
		color = addr[y_text * dda->texture->width + x_text];
		ft_draw_pixel(game->img, dda->x, y ++, color);
	}
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
		if (game->map[dda->map_j][dda->map_i] == '1')
			ft_hit_wall(dda, game);
	}
}
