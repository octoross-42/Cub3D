#include "cub3D.h"

int	f_and_c_cmp(t_paths *textures)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(i < 3)
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
	if (c == 'N' || c == 'E' || c == 'W' || c == 'N')
		return (1);
	return (0);
}

void	position_player(t_map *game, int i, int j)
{
	game->play_x_start = j;
	game->play_y_start = i;
}

void	change_map_get_player(t_map *game)
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
			else if (is_player(game->map[i][j]))
				position_player(game, i, j);
			j ++;
		}
		j = 0;
		i ++;
	}
}