/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits_copy_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jermarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 23:12:05 by jermarti          #+#    #+#             */
/*   Updated: 2025/02/21 23:12:07 by jermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	noob_free(void  *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_copy_map(t_map *game, char **map)
{
	int i;

	i = 0;
	while (i < (game->num_lines + 2))
	{
		if (map[i])
			noob_free(map[i]);
		i ++;
	}
	noob_free(map);
}

void	exit_bad_map(t_map *game)
{
	free_copy_map(game, game->map_copy);
	free_map(game->map);
	cringe_free(NULL, 0, NULL, game->textures);
	free(game);
}

void	release_textures(t_map *game)
{
	free(game->textures->n_path);
	free(game->textures->s_path);
	free(game->textures->e_path);
	free(game->textures->w_path);
	free(game->textures->ceiling);
	free(game->textures->floor);
	free(game->textures);
}
