/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits_copy_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jermarti <jermarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 23:12:05 by jermarti          #+#    #+#             */
/*   Updated: 2025/03/01 03:40:52 by jermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_part_map(char **map, int k)
{
	while (k > -1)
		free (map[k --]);
	free (map);
}

void	noob_free(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_copy_map(t_map *game, char **map)
{
	int	i;

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
