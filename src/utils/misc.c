/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jermarti <jermarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 03:23:44 by jermarti          #+#    #+#             */
/*   Updated: 2025/03/01 03:23:45 by jermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		printf("%s", map[i ++]);
}

void	free_map(char **map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (map[i])
			free(map[i ++]);
		free(map);
	}
}

int	ft_atoi(char *s)
{
	int	i;

	i = 0;
	while (*s)
	{
		i = i * 10 + (*s - 48);
		s ++;
	}
	return (i);
}

float	ft_abs(float n)
{
	if (n < 0)
		return (-n);
	return (n);
}

// void	print_int_array(int *colors)
// {
// 	int	i = 0;
// 	while(i <3)
// 	{
// 		printf("%d\t", colors[i ++]);
// 	}
// }