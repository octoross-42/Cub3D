/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_floor_and_ceiling.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jermarti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 23:12:40 by jermarti          #+#    #+#             */
/*   Updated: 2025/02/21 23:12:42 by jermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	until_comma(char *s)
{
	int	i;

	if (!s || *s == 0)
		return (0);
	i = 0;
	while (s[i] && s[i] != ',')
		i ++;
	return (i);
}

char	*strdupcomma(char *s)
{
	char	*ret;
	int		i;
	int		j;

	if (!s || *s == 0)
		return (NULL);
	i = until_comma(s);
	if (!i)
		return (NULL);
	ret = malloc((sizeof(char) * i) + 1);
	if (!ret)
		return (NULL);
	j = 0;
	while (j < i)
	{
		ret[j] = s[j];
		j ++;
	}
	ret[j] = 0;
	return (ret);
}

void	give_values(int k, int i, t_paths *paths, char c)
{
	if (c == 'c')
		paths->c_col[i] = k;
	else
		paths->f_col[i] = k;
}

int	check_floor_and_ceiling(char *s, int k, t_paths* paths, char c)
{
	char	*sc;
	int		i;

	sc = s;
	while (*s)
	{
		if (*s > '9' || *s < '0')
			return (0);
		s ++;
	}
	i = ft_atoi(sc);
	if (i > 255)
	{
		printf("Error, bad color value for floor or ceiling\n");
		return (0);
	}
	give_values(i, k, paths, c);
	return (1);
}

int	check_values(char *s, t_paths *paths, char c)
{
	char	*s1;
	char	*s2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s2 = ft_strncpy(s, ft_len(s) - 1);
	if (!s2)
		return (printf("Error mallocing something\n"), 0);
	while (i < 3)
	{
		s1 = strdupcomma(&s2[j]);
		if (!s1)
			return (free(s2), 0);
		if (!check_floor_and_ceiling(s1, i, paths, c))
			return(free(s1), free(s2), 0);
		free(s1);
		i ++;
		j = j + until_comma(&s2[j]) + 1;
		if ((j == ft_len(s) && i != 3) || (j != ft_len(s) && i == 3))
			return (free(s2), 0);
	}
	return (free(s2), 1);
}

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
