#include "cub3D.h"

char	*ft_strncpy(const char *src, int size)
{
	int	i;
	char	*dst;

	i = 0;
	if (size == 0)
		return (NULL);
	dst = malloc(sizeof(char) * (size + 1));
	if (!dst)
		return (NULL);
	while (src[i] && i < size)
	{
		dst[i] = src[i];
		i ++;
	}
	dst[i] = '\0';
	return (dst);
}

int	check_north(char *s, t_rules *ways, t_paths *paths)
{
	int		i;
	char	*s1;

	if (ways->north == 1)
	{
		ways->north ++;
		return (printf("Error, duplicate line for North texture\n"), 0);
	}
	while (*s == ' ')
		s ++;
	s1 = ft_strncpy(s, ft_len(s) - 1);
	i = open(s1, O_RDONLY);
	if (i == -1)
	{
		printf("Error opening image for North texture\n");
		return (noob_free(s1), 0);
	}
	else
	{
		close(i);
		ways->north ++;
		paths->n_path = s1;
		return (1);
	}
}

int	check_south(char *s, t_rules *ways, t_paths *paths)
{
	int		i;
	char	*s1;

	if (ways->south == 1)
	{
		ways->south ++;
		return (printf("Error, duplicate line for South texture\n"), 0);
	}
	while (*s == ' ')
		s ++;
	s1 = ft_strncpy(s, ft_len(s) - 1);
	i = open(s1, O_RDONLY);
	if (i == -1)
	{
		printf("Error opening image for South texture\n");
		return (noob_free(s1), 0);
	}
	else
	{
		close(i);
		ways->south ++;
		paths->s_path = s1;
		return (1);
	}
}

int	check_west(char *s, t_rules *ways, t_paths *paths)
{
	int		i;
	char	*s1;

	if (ways->west == 1)
	{
		ways->west ++;
		return (printf("Error, duplicate line for West texture\n"), 0);
	}
	while (*s == ' ')
		s ++;
	s1 = ft_strncpy(s, ft_len(s) - 1);
	i = open(s1, O_RDONLY);
	if (i == -1)
	{
		printf("Error opening image for West texture\n");
		return (noob_free(s1), 0);
	}
	else
	{
		close(i);
		ways->west ++;
		paths->w_path = s1;
		return (1);
	}
}

int	check_east(char *s, t_rules *ways, t_paths *paths)
{
	int		i;
	char	*s1;

	if (ways->east == 1)
	{
		ways->east ++;
		return (printf("Error, duplicate line for East texture\n"), 0);
	}
	while (*s == ' ')
		s ++;
	s1 = ft_strncpy(s, ft_len(s) - 1);
	i = open(s1, O_RDONLY);
	if (i == -1)
	{
		printf("Error opening image for East texture\n");
		return (noob_free(s1), 0);
	}
	else
	{
		close(i);
		ways->east ++;
		paths->e_path = s1;
		return (1);
	}
}