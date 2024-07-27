#include "mlx_linux/mlx.h"
#include "get_next_line/get_next_line.h"
#include "ft_printf/ft_printf.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_map {
        char    *path;
        size_t  height;
        size_t  width;
	size_t	Ex;
	size_t	Pos;
	size_t	Coll;
	int	fd;
	char	**grid;
	char	**highlight_grid;
	size_t	exit_acc;
	size_t	coll_acc;
}       t_map;

typedef struct s_pxy {
	size_t	x;
	size_t	y;
}	t_pxy;

typedef struct s_sprite {
	size_t	width;
	size_t	height;
	void	*img;
}	t_sprite;

typedef struct s_main {
	void	*mlx_ptr;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int	bpp;
	int	line_size;
	int	endian;
	t_map	map;
	t_pxy	p_pos;
}	t_main;

int     check_map_name(char *map_name)
{
        int     i;

        i = 0;
        while (map_name[i] != '\0')
                i++;
        if (map_name[i - 1] == 'r' && map_name[i - 2] == 'e' && map_name[i - 3] == 'b' && map_name[i - 4] == '.')
                return (0);
        return (1);
}

void    vars_init(t_map *map, char *map_path)
{
        char    *line;

        map->path = map_path;
        map->height = 0;
        map->width = 0;
        map->Ex = 0;
        map->Pos = 0;
        map->Coll = 0;
        map->exit_acc = 0;
        map->coll_acc = 0;
}

size_t  ft_strlenmap(char *line)
{
        int     i;

        i = 0;
        while (line[i] && line[i] != '\n')
                i++;
        return (i);
}

void    parse_map(t_map *map, t_pxy *p_pos)
{
        int     fd;
        char    *line;
        int     line_samelen;

        fd = open(map->path, O_RDONLY);
        line = get_next_line(fd);
        map->width = ft_strlenmap(line);
        while (line != NULL)
        {
                if (ft_strlenmap(line) != map->width)
                        line_samelen = 1;
                map->height++;
                line = get_next_line(fd);
        }
        close(fd);
        ft_printf("map width : %d\n", map->width); // à enlever
        ft_printf("map height : %d\n\n", map->height); // à enlever
        if (map->width == map->height || map->width == 0 || map->height == 0 || line_samelen == 1)
               exit (ft_printf("Your map is not rectangular or there's nothing in it.\n"));
}

void    allocate_grids(t_map *map)
{
        int     i;
        int     j;

        i = 0;
        j = 0;
        map->grid = (char **)malloc(sizeof(char *) * map->height + 1);
        map->highlight_grid = (char **)malloc(sizeof(char *) * map->height + 1);
        while (i < map->height)
        {
                map->grid[i] = (char *)malloc(sizeof(char) * map->width + 1);
                map->highlight_grid[i] = (char *)malloc(sizeof(char) * map->width + 1);
                i++;
        }
        i = 0;
        while (i < map->height)
        {
                while (j < map->width)
                {
                        map->highlight_grid[i][j] = '0';
                        j++;
                }
                map->highlight_grid[i][j] = '\0';
                i++;
                j = 0;
        }
        map->highlight_grid[i] = NULL;
}

void    grid_init(t_map *map)
{
        char    *line;
        int     j;
        int     i;

        i = 0;
        j = 0;

        map->fd = open(map->path, O_RDONLY);
        line = get_next_line(map->fd);
        allocate_grids(map);
        while (i < map->height)
        {
                while (line[j] && line[j] != '\n')
                {
                        map->grid[i][j] = line[j];
                        j++;
                }
                map->grid[i][j] = '\0';
                i++;
                j = 0;                                                                                                                               line = get_next_line(map->fd);
        }
        map->grid[i] = NULL;
        close(map->fd);
}

void    check_walls1(t_map *map)
{
        int     i;

        i = 0;
        while (i < map->width)
        {
                if (map->grid[0][i] != '1')
                        exit (ft_printf("Your map is not fully enclosed !\n"));
                i++;
        }
        i = 0;
        while (i < map->width)
        {
                if (map->grid[map->height - 1][i] != '1')
                        exit (ft_printf("Your map is not fully enclosed !\n"));
                i++;
        }
}

void    check_walls2(t_map *map)
{
        int     i;

        i = 1;
        while (i < map->height - 1)
        {
                if (map->grid[i][0] != '1')
                        exit (ft_printf("Your map is not fully enclosed !\n"));
                if (map->grid[i][map->width - 1] != '1')
                        exit (ft_printf("Your map is not fully enclosed !\n"));
                i++;
        }
}

void    check_epc(t_map *map, t_pxy *p_pos)
{
        int     i;
        int     j;

        i = 1;
        j = 0;
        while (i < map->height - 1)
        {
                while (map->grid[i][j] != '\0')
                {
                        if (map->grid[i][j] == 'E')
                                map->Ex++;
                        if (map->grid[i][j] == 'P')
                        {
                                map->Pos++;
                                p_pos->x = j;
                                p_pos->y = i;
                        }
                        if (map->grid[i][j] == 'C')
                                map->Coll++;
                        j++;
                }
                j = 0;
                i++;
        }
        ft_printf("map Exits : %d\n", map->Ex); // à enlever
        ft_printf("map Positions : %d\n", map->Pos); // à enlever
        ft_printf("map Collectibles : %d\n\n", map->Coll); // à enlever
        if (map->Ex != 1 || map->Pos != 1 || map->Coll < 1)                                                                                          exit (ft_printf("Verify that there are only one Exit, one Position and at least one Collectible!\n"));
}

void    check_path(t_map *map, size_t x, size_t y)
{
        if (map->grid[y][x] == '1' || map->highlight_grid[y][x] == '1' || x < 0 || y < 0 || x > map->width || y > map->height)
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

void	sprites_init(t_main *main)
{
	
}

int	main(int argc, char *argv[])
{
	t_main main;

	if (argc != 2)
		return (ft_printf("No map file was entered or to much files were entered.\n"));
	if (check_map_name(argv[1]) == 1)
		return (ft_printf("Map name is incorrect.\n"));
	vars_init(&main.map, argv[1]);
	parse_map(&main.map, &main.p_pos);
	grid_init(&main.map);
	check_walls1(&main.map);
	check_walls2(&main.map);
	check_epc(&main.map, &main.p_pos);
	check_path(&main.map, main.p_pos.x, main.p_pos.y);
	ft_printf("exit found : %d\n", main.map.exit_acc); // à enlever
	ft_printf("collectibles found : %d\n", main.map.coll_acc); // à enlever
	if (main.map.exit_acc != 1 || main.map.coll_acc != main.map.Coll)
		return (ft_printf("Your map is invalid because the exit or collectibles aren't accessible.\n"));
	main.mlx_ptr = mlx_init();
	main.mlx_win = mlx_new_window(main.mlx_ptr, 960, 540, "so_long");
	main.img = mlx_new_image(main.mlx_ptr, 960, 540);
	main.addr = mlx_get_data_addr(main.img, &main.bpp, &main.line_size, &main.endian);
	sprites_init(&main);

	mlx_loop(main.mlx_ptr);
	return (0);
}
