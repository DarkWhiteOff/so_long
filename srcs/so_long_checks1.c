/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_checks2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:12:52 by zamgar            #+#    #+#             */
/*   Updated: 2024/10/04 20:19:35 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	empty_line_check(char *line, int fd)
{
	if (line == NULL)
		exit (ft_printf("Error\nYou entered an empty map !\n"));
	if (line[0] == '\n' || line[0] == '\0')
	{
		free(line);
		close(fd);
		exit (ft_printf("Error\nYour map has one or more empty lines.\n"));
	}
}

void	parse_map(t_map *map)
{
	int		fd;
	char	*l;
	int		line_samelen;

	line_samelen = 0;
	fd = open(map->path, O_RDONLY);
	if (fd < 0 || read(fd, 0, 0) < 0)
		exit (ft_printf("Error\nfd not working."));
	l = get_next_line(fd, map);
	empty_line_check(l, fd);
	map->w = strlenmap(l, map);
	while (l)
	{
		if (strlenmap(l, map) != map->w || strlenmap(l, map) > map->sc_s.x / 48)
			line_samelen = 1;
		map->h++;
		empty_line_check(l, fd);
		free(l);
		l = get_next_line(fd, map);
	}
	close(fd);
	if (map->w == map->h || map->w == 0 || map->h == 0 || line_samelen == 1)
		exit (ft_printf("Error\nMap not rectangular / nothing in it.\n"));
	if (map->h > map->sc_s.y / 48)
		exit (ft_printf("Error\nYour screen is too small for this map !"));
}

void	check_walls1(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->w)
	{
		if (map->grid[0][i] != '1')
		{
			free_grids(map);
			exit (ft_printf("Error\nYour map is not fully enclosed !\n"));
		}
		i++;
	}
	i = 0;
	while (i < map->w)
	{
		if (map->grid[map->h - 1][i] != '1')
		{
			free_grids(map);
			exit (ft_printf("Error\nYour map is not fully enclosed !\n"));
		}
		i++;
	}
}

void	check_walls2(t_map *map)
{
	int	i;

	i = 1;
	while (i < map->h - 1)
	{
		if (map->grid[i][0] != '1')
		{
			free_grids(map);
			exit (ft_printf("Error\nYour map is not fully enclosed !\n"));
		}
		if (map->grid[i][map->w - 1] != '1')
		{
			free_grids(map);
			exit (ft_printf("Error\nYour map is not fully enclosed !\n"));
		}
		i++;
	}
}

int	check_map_limits_epc(t_map *map, int y, int x)
{
	if (map->grid[y][x] != 'E' && map->grid[y][x] != 'P' && map->grid[y][x]
		!= 'C' && map->grid[y][x] != '0' && map->grid[y][x] != '1')
		return (0);
	return (1);
}