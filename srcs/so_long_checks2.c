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

void	is_epc(t_map *map, int i, int j, t_pxy *p_pos)
{
	if (map->grid[i][j] == 'E')
		map->Ex++;
	if (map->grid[i][j] == 'P')
	{
		map->Pos++;
		save_pos(p_pos, j, i);
	}
	if (map->grid[i][j] == 'C')
		map->Coll++;
}

void    check_epc(t_map *map, t_pxy *p_pos, t_pxy *e_pos)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i < map->h - 1)
	{
		while (map->grid[i][j] != '\0')
		{
			is_epc(map, i, j, p_pos);
			if (map->grid[i][j] != 'E' && map->grid[i][j] != 'P' && map->grid[i][j] != 'C' && map->grid[i][j] != '0' && map->grid[i][j] != '1')
			{
				free_grids(map);
				exit (ft_printf("Error\nYour map contains an unrecognized character."));
			}
			j++;
		}
		j = 0;
		i++;
	}
	if (map->Ex != 1 || map->Pos != 1 || map->Coll < 1)
	{
		free_grids(map);
		exit (ft_printf("Error\nVerify that there are only one Exit, one Position and at least one Collectible!\n"));
	}
}

void    check_path(t_map *map, size_t x, size_t y)
{
    if (map->grid[y][x] == '1' || map->highlight_grid[y][x] == '1' || x < 0 || y < 0 || x > map->w || y > map->h)
        return ;
    map->highlight_grid[y][x] = '1';
    if (map->grid[y][x] == 'E')
        map->exit_acc = 1;
    if (map->grid[y][x] == 'C')
        map->coll_acc++;
    check_path(map, x - 1, y);
    check_path(map, x + 1, y);
    check_path(map, x, y - 1);
    check_path(map, x, y + 1);
    return ;
}

void    allocate_grids(t_map *map)
{
    int     i;
    int     j;

    i = 0;
    j = 0;
    map->grid = (char **)malloc(sizeof(char *) * map->h + 1);
    map->highlight_grid = (char **)malloc(sizeof(char *) * map->h + 1);
    while (i < map->h)
    {
            map->grid[i] = (char *)malloc(sizeof(char) * map->w + 1);
            map->highlight_grid[i] = (char *)malloc(sizeof(char) * map->w + 1);
            i++;
    }
    i = 0;
    while (i < map->h)
    {
        while (j < map->w)
        {
            map->highlight_grid[i][j] = '0';
            j++;
        }
        map->highlight_grid[i][j] = '\0';
        i++;
        j = 0;
    }
}

void    grid_init(t_main *main)
{
    char    *line;
    int     j;
    int     i;

    i = 0;
    j = 0;
    main->map.fd = open(main->map.path, O_RDONLY);
	if (main->map.fd < 0 || read(main->map.fd, 0, 0) < 0)
		exit (ft_printf("Error\nfd not working."));
    line = get_next_line(main->map.fd, &main->map);
    allocate_grids(&main->map);
    while (i < main->map.h)
    {
        while (line[j] && line[j] != '\n')
        {
			if (line[j] == 'E')
                save_pos(&main->e_pos, j, i);
			main->map.grid[i][j] = line[j];
            j++;
        }
        main->map.grid[i++][j] = '\0';
        j = 0;
		free(line);
		line = get_next_line(main->map.fd, &main->map);
    }
    close(main->map.fd);
}
