/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   void_fill_temp_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jermarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 23:14:15 by jermarti          #+#    #+#             */
/*   Updated: 2025/02/21 23:14:17 by jermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_token(char c)
{
	if (c == 'N' || c == 'W' || c == 'E' || c == 'O' || c == '0')
		return (1);
	return (0);
}

void	ty_lugway_bis(t_map *game, int i, int j, t_search *values)
{
	if (game->map_copy[i][j] == ' ')
	{
		game->map_copy[i][j] = '2';
		if (game->map_copy[i][j + 1] == 'B' || game->map_copy[i + 1][j] == 'B'
			|| game->map_copy[i][j - 1] == 'B' || game->map_copy[i - 1][j] == 'B')
			values->wall = 1;
		if (is_token(game->map_copy[i][j + 1])
			|| is_token(game->map_copy[i + 1][j])
			|| is_token(game->map_copy[i][j - 1])
			|| is_token(game->map_copy[i - 1][j]))
			values->zero = 1;
		if (i + 1 < game->max_width)
			ty_lugway_bis(game, i + 1, j, values);
		if (j + 1 < game->num_lines + 2)
			ty_lugway_bis(game, i, j + 1, values);
		if (i - 1 >= 1)
			ty_lugway_bis(game, i - 1, j, values);
		if (j - 1 >= 1)
			ty_lugway_bis(game, i, j - 1, values);
	}
}

int	last_check(t_map *game)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (game->map_copy[i])
	{
		while (game->map_copy[i][j])
		{
			if (is_token(game->map_copy[i][j]))
			{
				if (game->map_copy[i + 1][j] == 'B'
					|| game->map_copy[i][j + 1] == 'B'
					|| game->map_copy[i - 1][j] == 'B'
					|| game->map_copy[i][j - 1] == 'B')
					return (0);
			}
			j ++;
		}
		j = 1;
		i ++;
	}
	return (1);
}

int	apply_algo(t_map *game, t_search *values)
{
	int	i;
	int	j;

	i = 1;
	j = 1;
	while (game->map_copy[i])
	{
		while (game->map_copy[i][j])
		{
			if (game->map_copy[i][j] == ' ')
				ty_lugway_bis(game, i, j, values);
			if (values->wall == 1 && values->zero == 1)
				return (0);
			j ++;
			values->wall = 0;
			values->zero = 0;
		}
		j = 1;
		i ++;
	}
	if (!(last_check(game)))
		return (0);
	return (1);
}

int	is_map_closed(t_map *game)
{
	int i;
	t_search *values;

	values = malloc(sizeof(t_search));
	if (!values)
	{
		printf("Error allocating a struct during map parsing\n");
		return (free_copy_map(game, game->map_copy), 0);
	}
	values->wall = 0;
	values->zero = 0;
	i = apply_algo(game, values);
	if (!i)
		printf("Error, map is not closed\n");
	free(values);
	return (i);
}
	// print_map(game->map_copy);
