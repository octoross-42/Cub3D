/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jermarti <jermarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 03:23:02 by jermarti          #+#    #+#             */
/*   Updated: 2025/03/01 05:13:39 by jermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	f_and_c_cmp(t_paths *textures)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 3)
	{
		if (textures->f_col[i] == textures->c_col[i])
			j ++;
		i ++;
	}
	if (j == 3)
		return (1);
	return (0);
}

void	empty_buffer(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
	}
}

int	is_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (1);
	return (0);
}

int	position_player(t_map *game, int i, int j)
{
	game->player = (t_player *)malloc(sizeof(t_player));
	if (!game->player)
		return (0);
	game->player->x = j + 0.5;
	game->player->y = i + 0.5;
	game->player->dx = (game->direction == 'E') - (game->direction == 'W');
	game->player->dy = (game->direction == 'S') - (game->direction == 'N');
	game->player->camera_plane_dx = -FOV * game->player->dy;
	game->player->camera_plane_dy = FOV * game->player->dx;
	return (1);
}

int	change_map_get_player(t_map *game)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (game->map[i])
	{
		while (game->map[i][j])
		{
			if (game->map[i][j] == ' ')
				game->map[i][j] = '1';
			else if (is_player(game->map[i][j]) && !position_player(game, i, j))
			{
				printf("Error mallocing player structure\n");
				return (0);
			}
			j ++;
		}
		j = 0;
		i ++;
	}
	return (1);
}
