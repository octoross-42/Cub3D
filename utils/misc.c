#include "cub3D.h"

void	print_map(char **map)
{
	int	i = 0;

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

// void	print_int_array(int *colors)
// {
// 	int	i = 0;
// 	while(i <3)
// 	{
// 		printf("%d\t", colors[i ++]);
// 	}
// }