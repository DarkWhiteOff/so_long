/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:47:04 by zamgar            #+#    #+#             */
/*   Updated: 2024/06/24 13:24:00 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

char	*read_into_buffer(int fd, char *save, char *buffer)
{
	int		nb_read;
	char	*temp;

	nb_read = 1;
	while (nb_read > 0)
	{
		nb_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_read < 0)
		{
			free(save);
			return (NULL);
		}
		else if (nb_read == 0)
			break ;
		buffer[nb_read] = '\0';
		if (save == NULL)
			save = ft_strdup("");
		temp = save;
		if (temp != NULL && buffer != NULL)
			save = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (save);
}

char	*prepare_nextline(char	*newLine)
{
	char	*save;
	int		i;

	i = 0;
	while (newLine[i] != '\n' && newLine[i] != '\0')
		i++;
	if (newLine[i] == '\0' || newLine[i + 1] == '\0')
		return (NULL);
	save = ft_substr(newLine, i + 1, ft_strlen(newLine) - i);
	if (save == NULL)
	{
		free(save);
		return (NULL);
	}
	newLine[i + 1] = '\0';
	return (save);
}

char	*get_next_line(int fd, t_map *map)
{
	char		*buffer;
	char		*n_l;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	n_l = read_into_buffer(fd, save, buffer);
	free(buffer);
	if (n_l == NULL)
	{
		free(save);
		save = NULL;
		return (NULL);
	}
	save = prepare_nextline(n_l);
	if (n_l[0] == '\0' || n_l[0] == '\n' || ft_strlen(n_l) > map->sc_s.x / 48)
		free(save);
	return (n_l);
}

/*int	main(void)
{
	int	fd = open("1char.txt", O_RDONLY);
	int	line;
	int	i;

	line = 1;
	i = 0;
	while (i < 4)
	{
		printf("Line %d : %s\n", line, get_next_line(fd));
		i++;
		line++;
	}
	return (0);
}*/
