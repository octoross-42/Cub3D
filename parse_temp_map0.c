#include "cub3D.h"

char	*last_line(t_map *game, char *to_copy)
{
	char	*line;
	int		k;
	int		i;

	k = ft_len(to_copy);
	line = malloc(sizeof(char) * (game->max_width + 2));
	if (!line)
		return (NULL);
	i = 0;
	line[0] = 'B';
	while (i < k + 1)
	{
		line[i + 1] = to_copy[i];
		i ++;
	}
	while (i < (game->max_width))
		line[i ++] = ' ';
	line[i] = 'B';
	line[i + 1] = 0;
	return (line);
}

char	*extern_lines(t_map *game)
{
	char	*line;
	int		k;
	int		i;

	k = game->max_width + 1;
	line = malloc(sizeof(char) * (k + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (i < k)
		line[i ++] = 'B';
	line[i] = 0;
	return (line);
}

char	*copy_line(int i, t_map *game)
{
	char	*line;
	int		j;
	int		k;

	line = malloc(sizeof(char) * game->max_width + 2);
	if (!line)
		return (NULL);
	j = 0;
	k = ft_len(game->map[i]);
	line[j] = 'B';
	while (j < k)
	{
		line[j + 1] = game->map[i][j];
		j ++;
	}
	while (j < (game->max_width))
		line[j ++] = ' ';
	line[j] = 'B';
	line[j + 1] = 0;
	return (line);
}

char	**copy_map(t_map *game)
{
	int	i;

	if (!game->map)
		return (NULL);
	i = 1;
	game->map_copy = malloc(sizeof(char *) * (game->num_lines + 3));
	if (!(game->map_copy))
		return (NULL);
	game->map_copy[0] = extern_lines(game);
	while (i < game->num_lines)
	{
		game->map_copy[i] = copy_line(i - 1, game);
		if (!(game->map_copy[i]))
			return (free_copy_map(game, game->map_copy), NULL);
		i ++;
	}
	game->map_copy[i] = last_line(game, game->map[game->num_lines - 1]);
	game->map_copy[i + 1] = extern_lines(game);
	game->map_copy[i + 2] = NULL;
	if (!game->map_copy[i + 1] || !game->map_copy[i] || !game->map_copy[0])
		return (free_copy_map(game, game->map_copy), NULL);
	return (game->map_copy);
}