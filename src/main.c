/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jermarti <jermarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 03:33:44 by jermarti          #+#    #+#             */
/*   Updated: 2025/03/01 04:03:25 by jermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (s2[0]);
	if (!s2)
		return (s1[0]);
	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i ++;
	return (s1[i] - s2[i]);
}

void	init_things(t_rules *w, t_paths *t)
{
	w->north = 0;
	w->south = 0;
	w->east = 0;
	w->west = 0;
	w->floor = 0;
	w->ceiling = 0;
	t->n_path = NULL;
	t->s_path = NULL;
	t->e_path = NULL;
	t->w_path = NULL;
	t->ceiling = NULL;
	t->floor = NULL;
}

int	check_map_content(char *map, t_map *game)
{
	int		fd;
	t_rules	*ways;
	int		i;

	i = 0;
	ways = malloc(sizeof(t_rules));
	if (!ways)
		return (write(2, "Error, malloc error\n", 20), 0);
	game->textures = malloc(sizeof(t_paths));
	if (!game->textures)
		return (free(ways), write(2, "Error, malloc error\n", 20), 0);
	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		free(ways);
		free(game->textures);
		free(game);
		write(2, "Error, can't open map file.\n", 28);
		exit(EXIT_FAILURE);
	}
	init_things(ways, game->textures);
	if (map_textures(fd, ways, game->textures))
		i = map_content(fd, game);
	return (i);
}

int	check_map_ext(char *s)
{
	int	i;

	i = ft_len(s);
	if (i < 4)
	{
		printf("Error, program requires a .cub file to work\n");
		return (0);
	}
	if (ft_strcmp(&s[i - 4], ".cub"))
	{
		printf("Error, program requires a .cub file to work\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_map	*game;

	if (argc != 2)
	{
		printf("Error, feed this program with a .cub file only\n");
		exit(EXIT_SUCCESS);
	}
	game = malloc(sizeof(t_map));
	if (!game)
		return (printf("Error allocing memory for the main structure\n"), 1);
	game->max_width = 0;
	game->player_nbr = 0;
	game->pos_mouse = 540;
	if (!check_map_ext(argv[1]))
		return (free(game), 0);
	if (!check_map_content(argv[1], game))
		return (release_textures(game), free(game), 0);
	if (!is_map_closed(game))
		return (exit_bad_map(game), 0);
	free_copy_map(game, game->map_copy);
	if (go_to_mlx_functions(game))
		free_mlx(game);
	free_images(game);
	final_free(game);
	return (0);
}
	// print_int_array(game->textures->c_col);