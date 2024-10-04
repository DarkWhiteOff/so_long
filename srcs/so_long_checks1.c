#include "../includes/so_long.h"

void    save_pos(t_pxy *x_pos, int j, int i)
{
    x_pos->x = j;
    x_pos->y = i;
}

void    empty_line_check(char *line, int fd)
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

void    parse_map(t_map *map, t_pxy *p_pos)
{
	int     fd;
    char    *line;
    int     line_samelen;

	line_samelen = 0;
    fd = open(map->path, O_RDONLY);
	if (fd < 0 || read(fd, 0, 0) < 0)
		exit (ft_printf("Error\nfd not working."));
    line = get_next_line(fd, map);
    empty_line_check(line, fd);
	map->w = ft_strlenmap(line, map);
    while (line)
    {
        if (ft_strlenmap(line, map) != map->w || ft_strlenmap(line, map) > map->screen_size.x / 48)
            line_samelen = 1;
        map->h++;
		empty_line_check(line, fd);
		free(line);
    	line = get_next_line(fd, map);
    }
    close(fd);
    if (map->w == map->h || map->w == 0 || map->h == 0 || line_samelen == 1)
        exit (ft_printf("Error\nYour map is not rectangular or there's nothing in it.\n"));
    if (map->h > map->screen_size.y / 48)
        exit (ft_printf("Error\nYour screen is too small for this map !"));
}

void    check_walls1(t_map *map)
{
    int     i;

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

void    check_walls2(t_map *map)
{
    int     i;

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