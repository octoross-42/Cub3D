/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 22:07:24 by octoross          #+#    #+#             */
/*   Updated: 2025/02/23 21:49:39 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_draw_walls(t_map *map)
{
	int i = 0;
	while (map->map[i])
	{
		int j = 0;
		while (map->map[i][j])
			printf("%c", map->map[i][j++]);
		printf("\n");
		i++;
	}
    return (0);
}