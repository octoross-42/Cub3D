/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jermarti <jermarti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 03:21:06 by jermarti          #+#    #+#             */
/*   Updated: 2025/03/01 03:21:07 by jermarti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*shortstr(char *src)
{
	int		i;
	char	*dest;

	if (!src)
		return (NULL);
	i = 0;
	dest = malloc(sizeof(char) * (is_nl(src) + 2));
	if (!dest)
		return (NULL);
	while (i < is_nl(src) + 1)
	{
		dest[i] = src[i];
	i ++;
	}
	free(src);
	dest[i] = '\0';
	return (dest);
}

char	*holdtrim(char *hold)
{
	int		i;
	int		n;
	char	*new;

	if (!hold || ft_len(hold) == 0)
		return (NULL);
	i = 0;
	new = malloc(sizeof(char) * (ft_len(hold) - (is_nl(hold))));
	if (!new)
		return (NULL);
	n = is_nl(hold) + 1;
	if (n == ft_len(hold))
	{
		free(new);
		return (NULL);
	}
	while (hold[n])
		new[i ++] = hold[n ++];
	new[i] = '\0';
	return (new);
}

char	*process_buff(int fd, char *hold)
{
	int		n;
	char	*buff;

	buff = malloc (sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	n = 1;
	while (is_nl(hold) == -1 && n > 0)
	{
		n = read(fd, buff, BUFFER_SIZE);
		if (n < 0)
			return (free(buff), NULL);
		buff[n] = '\0';
		hold = ft_join(hold, buff);
		if (!hold)
		{
			free(buff);
			return (NULL);
		}
	}
	free(buff);
	return (hold);
}

char	*get_next_line(int fd)
{
	char		*ltp;
	static char	*hold = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ltp = process_buff(fd, hold);
	if (is_nl(ltp) == -1)
	{
		hold = ft_strdup(NULL);
		free(hold);
		return (ltp);
	}
	hold = holdtrim(ltp);
	return (shortstr(ltp));
}
