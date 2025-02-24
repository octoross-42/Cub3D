#include "cub3D.h"

int 	ft_len(char *s)
{
	int 	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] && s)
		i ++;
	return (i);
}

//checks at which index is the \n if there is one
int 	is_nl(char *s)
{
	int 	j;

	j = 0;
	if (!s)
		return (-1);
	while (s[j] && s[j] != '\n')
		j ++;
	if (s[j] == '\n')
		return (j);
	return (-1);
}

char	*ft_strdup(char *s)
{
	int 	i;
	char	*dest;

	if (!s || ft_len(s) == 0)
		return (NULL);
	dest = malloc(sizeof(char) * (ft_len(s) + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dest[i] = s[i];
		i ++;
	}
	dest[i] = '\0';
	return (dest);
}


char	*ft_join(char *hold, char *buff)
{
	char	*final;
	int 	i;
	int 	j;
	
	if (!hold && !buff)
		return (NULL);
	if (!hold)
		return (ft_strdup(buff));
	if (!buff)
		return (ft_strdup(hold));
	j = 0;
	i = 0;
	final = malloc(sizeof(char) * (ft_len(hold) + ft_len(buff) + 1));
	if (!final)
		return (NULL);
	while (hold[j])
	{
		final[j] = hold[j];
		j ++;
	}
	while (buff[i])
		final[j ++] = buff[i ++];
	final[j] = '\0';
	free(hold);
	return (final);
}