/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_textures.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: octoross <octoross@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 23:12:59 by jermarti          #+#    #+#             */
/*   Updated: 2025/02/22 22:04:42 by octoross         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	cringe_free(char *line, int fd, t_rules *w, t_paths *paths)
{
	while(line)
	{
		free(line);
		line = get_next_line(fd);
	}
	if (fd > 0)
		close(fd);
	if (paths)
	{
		if (paths->n_path)
			free(paths->n_path);
		if (paths->s_path)
			free(paths->s_path);
		if (paths->e_path)
			free(paths->e_path);
		if (paths->w_path)
			free(paths->w_path);
		if (paths->floor)
			free(paths->floor);
		if (paths->ceiling)
			free(paths->ceiling);
		free(paths);
	}
	if (w)
		free(w);
}

int	everything_set(t_rules *ways)
{
	if (ways->north == 1 && ways->south == 1 && ways->east == 1
		&& ways->west == 1 && ways->ceiling == 1 && ways->floor == 1)
		return (1);
	else if (ways->north > 1 || ways->south > 1 || ways->east > 1
		|| ways->west > 1 || ways->ceiling > 1 || ways->floor > 1)
		{
			printf("Error, duplicate found in the file\n");
			return (-1);
		}
	else
		return (0);
}

int	direction_check(char *s, t_rules *ways, t_paths *paths)
{
	if ((!strncmp(s, "NO ", 3)))
		return (check_north(s + 3, ways, paths));
	else if ((!strncmp(s, "SO ", 3)))
		return (check_south(s + 3, ways, paths));
	else if ((!strncmp(s, "WE ", 3)))
		return (check_west(s + 3, ways, paths));
	else if ((!strncmp(s, "EA ", 3)))
		return (check_east(s + 3, ways, paths));
	else if (!strncmp(s, "F ", 2))
		return (check_floor(s + 2, ways, paths));
	else if (!strncmp(s, "C ", 2))
		return (check_ceiling(s + 2, ways, paths));
	else
	{
		printf("Error, at least one line has bad input\n");
		return (0);
	}
}

int	parse_line(char	*line, t_rules *ways, t_paths *paths)
{
	if (!(strcmp(line, "\n")))
		return (1);
	while (*line == ' ')
		line ++;
	if (direction_check(line, ways, paths) == 0)
		return (0);
	return (1);
}

int	map_textures(int fd, t_rules *w, t_paths *p)
{
	char	*line;

	while (!(everything_set(w)))
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!parse_line(line, w, p))
			return (cringe_free(line, fd, w, NULL), 0);
		free(line);
	}
	if (!(everything_set(w)))
		return (cringe_free(NULL, fd, w, NULL), 0);
	if (everything_set(w) == -1)
		return (cringe_free(line, fd, w, NULL), 0);
	if (f_and_c_cmp(p))
	{
		empty_buffer(fd);
		cringe_free(NULL, fd, w, NULL);
		return (printf("Error, floor and ceiling are the same color\n"), 0);
	}
	return (free(w), 1);
}
