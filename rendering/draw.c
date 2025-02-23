/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 21:37:04 by octoross          #+#    #+#             */
/*   Updated: 2025/02/23 21:37:04 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_colorOfRgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}

void	ft_draw_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr
		+ (y * img->size_line
		+ x * (img->bpp / 8));
	*(int *)pixel = color;
}

t_img	*ft_init_image(t_mlx *mlx)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (!img)
		return (NULL);
	img->width = W_WIDTH;
	img->height = W_HEIGHT;
	img->img = mlx_new_image(mlx->co, img->width, img->height);
	img->addr = mlx_get_data_addr(img->img, &(img->bpp),
			&(img->size_line), &(img->endian));
	return (img);
}

int	ft_draw(t_map *game)
{
	// (void)game;
	game->img = ft_init_image(game->mlx);
	if (!(game->img))
		return (0);
	ft_draw_walls(game);
	mlx_put_image_to_window(game->mlx->co, game->mlx->win, game->img->img, 0, 0);
	return (1);
}