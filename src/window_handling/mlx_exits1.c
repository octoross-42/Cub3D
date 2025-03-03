/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_exits1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 04:46:55 by jermarti          #+#    #+#             */
/*   Updated: 2025/03/03 18:59:22 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	exit_minimap(t_map *game)
{
	free_images(game);
	free_mlx(game);
	final_free(game);
	free(game);
	exit(EXIT_FAILURE);
}

void	exit_image(t_map *game)
{
	mlx_destroy_image(game->mlx->co, game->textures->n_text.img);
	mlx_destroy_image(game->mlx->co, game->textures->e_text.img);
	mlx_destroy_image(game->mlx->co, game->textures->s_text.img);
	mlx_destroy_image(game->mlx->co, game->textures->w_text.img);
	free_mlx(game);
	final_free(game);
	free(game);
	exit(EXIT_FAILURE);
}

void	exit_images(t_map *game)
{
	free_mlx(game);
	final_free(game);
	free(game);
	exit(EXIT_FAILURE);
}

void	error_player(t_map *game)
{
	free_mlx(game);
	release_textures(game);
	free_map(game->map);
	free(game);
	exit(EXIT_FAILURE);
}

void	error_mlx(t_map *game)
{
	release_textures(game);
	free_map(game->map);
	free(game);
	exit(EXIT_FAILURE);
}
