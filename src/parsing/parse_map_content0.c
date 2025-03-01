/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_content0.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jermarti <jermarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 23:13:16 by jermarti          #+#    #+#             */
/*   Updated: 2025/03/01 03:40:45 by jermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

//have to free st_map here too
char	**get_map(char *st_map, t_map *game)
{
	int		i;
	int		k;
	int		l;

	i = 0;
	k = 0;
	l = 0;
	while (st_map[i])
	{
		while (st_map[i] != '\n' && st_map[i])
			i ++;
		if (st_map[i])
			i ++;
		game->map[k] = ft_strncpy(&st_map[l], i - l);
		if (!game->map[k])
			return (free_part_map(game->map, k - 1), free(st_map), NULL);
		k ++;
		if ((i - l) > game->max_width)
			game->max_width = i - l;
		l = i;
	}
	game->map[k] = NULL;
	return (free(st_map), game->map);
}

//frees st_map
char	**create_map(char *st_map, t_map *game)
{
	char	*trimmed_map;
	int		i;
	int		j;

	i = 0;
	j = 1;
	while (*st_map == '\n')
		st_map ++;
	trimmed_map = ft_strdup(st_map);
	if (!trimmed_map)
		return (NULL);
	while (trimmed_map[i])
	{
		if (trimmed_map[i] == '\n')
			j ++;
		i ++;
	}
	game->num_lines = j;
	game->map = malloc(sizeof(char *) * (j + 1));
	if (!game->map)
		return (free(trimmed_map), NULL);
	return (get_map(trimmed_map, game));
}

int	set_basics(char *st_map, t_map *game)
{
	while (*st_map)
	{
		if (*st_map == 'N' || *st_map == 'E'
			|| *st_map == 'W' || *st_map == 'S')
		{
			game->player_nbr ++;
			game->direction = *st_map;
		}
		st_map ++;
	}
	if (game->player_nbr == 1)
		return (1);
	printf("Error, no player or more than one player found\n");
	return (0);
}
//must return 0 if error; 1 if good. 
//directly fed to primary fn for 2nd half of the map

int	parse_stretched_map(char *st_map, t_map *game)
{
	int	i;

	i = 0;
	while (st_map[i])
	{
		if (st_map[i] == '1' || st_map[i] == '0' || st_map[i] == 'N'
			|| st_map[i] == 'E' || st_map[i] == 'W' || st_map[i] == 'S'
			|| st_map[i] == '\n' || st_map[i] == ' ')
			i ++;
		else
			return (printf("Error, bad token in file\n"), free(st_map), 0);
	}
	if (!set_basics(st_map, game))
		return (free(st_map), 0);
	game->map = create_map(st_map, game);
	game->map_copy = copy_map(game);
	if (!game->map_copy)
	{
		printf("Error mallocing a map or one of its line\n");
		return (free_map(game->map), free(st_map), 0);
	}
	free(st_map);
	return (1);
}
	// print_map(game->map_copy);
	// free_map(game->map_copy);

int	map_content(int fd, t_map *game)
{
	char	*stretched_map;
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (printf("Error, invalid map or malloc error\n"), 0);
	stretched_map = NULL;
	while (line)
	{
		stretched_map = ft_join(stretched_map, line);
		if (!stretched_map)
		{
			free(line);
			return (printf("Error while allocing memory for the map\n"), 0);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (parse_stretched_map(stretched_map, game));
}
