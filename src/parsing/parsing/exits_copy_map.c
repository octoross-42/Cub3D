/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits_copy_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 23:12:05 by jermarti          #+#    #+#             */
/*   Updated: 2025/02/23 23:02:31 by octoross         ###   ########.fr       */
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
