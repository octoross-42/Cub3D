/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_floor_and_ceiling1.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jermarti <jermarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 03:39:53 by jermarti          #+#    #+#             */
/*   Updated: 2025/03/01 03:44:14 by jermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_ceiling(char *s, t_rules *ways, t_paths *paths)
{
	if (ways->ceiling == 1)
	{
		ways->ceiling ++;
		return (printf("Error, duplicate line for ceiling\n"), 0);
	}
	while (*s == ' ')
		s ++;
	if (!check_values(s, paths, 'c'))
		return (printf("Error, wrong input line for ceiling\n"), 0);
	else
	{
		ways->ceiling ++;
		return (1);
	}
}

int	check_floor(char *s, t_rules *ways, t_paths *paths)
{
	if (ways->floor == 1)
	{
		ways->floor ++;
		return (printf("Error, duplicate line for floor\n"), 0);
	}
	while (*s == ' ')
		s ++;
	if (!check_values(s, paths, 'f'))
		return (printf("Error, wrong input line for floor\n"), 0);
	else
	{
		ways->floor ++;
		return (1);
	}
}
