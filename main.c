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
	size_t	player_on_exit;
}       t_map;

typedef struct s_pxy {
	size_t	x;
	size_t	y;
}	t_pxy;

typedef struct s_sprite {
	int	width;
	int	height;
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
	t_pxy	e_pos;
	t_sprite	spr_wall;
	t_sprite	spr_floor;
	t_sprite	spr_coll1;
	t_sprite	spr_coll2;
	t_sprite	spr_floor_coll;
	t_sprite	spr_door_close;
	t_sprite	spr_door_open;
	t_sprite	spr_player_front;
	t_sprite	spr_player_back;
	t_sprite	spr_player_side;
	t_sprite	spr_you_win;
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
	map->player_on_exit = 0;
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

void    grid_init(t_main *main)
{
        char    *line;
        int     j;
        int     i;

        i = 0;
        j = 0;

        main->map.fd = open(main->map.path, O_RDONLY);
        line = get_next_line(main->map.fd);
        allocate_grids(&main->map);
        while (i < main->map.height)
        {
                while (line[j] && line[j] != '\n')
                {
			if (line[j] == 'E')
			{
				main->e_pos.x = j;
                                main->e_pos.y = i;
			}
			main->map.grid[i][j] = line[j];
                        j++;
                }
                main->map.grid[i][j] = '\0';
                i++;
                j = 0;                                                                                                                               line = get_next_line(main->map.fd);
        }
        main->map.grid[i] = NULL;
        close(main->map.fd);
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

void    check_epc(t_map *map, t_pxy *p_pos, t_pxy *e_pos)
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

void	free_what_to_free(t_main *main)
{
	int	i;

	i = 0;
	while (main->map.highlight_grid[i] != NULL)
	{
		free(main->map.highlight_grid[i]);
		i++;
	}
	free(main->map.highlight_grid);
}

void	sprites_init(t_main *main)
{
	main->spr_wall.img = mlx_xpm_file_to_image(main->mlx_ptr, "sprites_tiles/32x32/spr_wall.xpm", &main->spr_wall.width, &main->spr_wall.height);
	main->spr_floor.img = mlx_xpm_file_to_image(main->mlx_ptr, "sprites_tiles/32x32/spr_floor.xpm", &main->spr_floor.width, &main->spr_floor.height);
	main->spr_floor_coll.img = mlx_xpm_file_to_image(main->mlx_ptr, "sprites_tiles/32x32/spr_floor_coll.xpm", &main->spr_floor_coll.width, &main->spr_floor_coll.height);
	main->spr_coll2.img = mlx_xpm_file_to_image(main->mlx_ptr, "sprites_tiles/32x32/spr_coll2.xpm", &main->spr_coll2.width, &main->spr_coll2.height);
	main->spr_door_close.img = mlx_xpm_file_to_image(main->mlx_ptr, "sprites_tiles/32x32/spr_door_close.xpm", &main->spr_door_close.width, &main->spr_door_close.height);
	main->spr_player_front.img = mlx_xpm_file_to_image(main->mlx_ptr, "sprites_tiles/32x32/spr_player_front.xpm", &main->spr_player_front.width, &main->spr_player_front.height);
	if (!main->spr_player_front.img)
		ft_printf("FAILED");
	main->spr_player_back.img = mlx_xpm_file_to_image(main->mlx_ptr, "sprites_tiles/32x32/spr_player_back.xpm", &main->spr_player_back.width, &main->spr_player_back.height);
	main->spr_player_side.img = mlx_xpm_file_to_image(main->mlx_ptr, "sprites_tiles/32x32/spr_player_side.xpm", &main->spr_player_side.width, &main->spr_player_side.height);
	main->spr_you_win.img = mlx_xpm_file_to_image(main->mlx_ptr, "sprites_tiles/32x32/spr_you_win.xpm", &main->spr_you_win.width, &main->spr_you_win.height);
}

int     close_window(t_main *main)
{
        mlx_destroy_window(main->mlx_ptr, main->mlx_win);
        exit (0);
}

void    actualise_map_data(t_main *main)
{
        int     x;
        int     y;

        x = main->p_pos.x;
        y = main->p_pos.y;

        if (main->map.grid[y][x] == 'C')
                main->map.Coll--;
        if (main->map.Coll == 0)
		main->map.grid[main->e_pos.y][main->e_pos.x] = 'E';
        main->map.grid[y][x] = 'P';
	if (main->map.grid[main->e_pos.y][main->e_pos.x] == 'P' && main->map.Coll == 0)
		main->map.player_on_exit = 1;

        /*int     i = 0;
        int     j = 0;

        while (main->map.grid[i] != NULL)
        {
                while (main->map.grid[i][j] != '\0')
                {
                        ft_printf("%c ", main->map.grid[i][j]);
                        j++;
                }
                ft_printf("\n");
                j = 0;
                i++;
        } // à enlever*/
}

void	update_player_pos(t_main *main, char c)
{
	main->map.grid[main->p_pos.y][main->p_pos.x] = '0';
	if (c == 'Z' && main->map.grid[main->p_pos.y - 1][main->p_pos.x] != '1')
		main->p_pos.y = main->p_pos.y - 1;
	if (c == 'Q' && main->map.grid[main->p_pos.y][main->p_pos.x - 1] != '1')
		main->p_pos.x = main->p_pos.x - 1;
	if (c == 'S' && main->map.grid[main->p_pos.y + 1][main->p_pos.x] != '1')
		main->p_pos.y = main->p_pos.y + 1;
	if (c == 'D' && main->map.grid[main->p_pos.y][main->p_pos.x + 1] != '1')
		main->p_pos.x = main->p_pos.x + 1;
	actualise_map_data(main);
}

int     key_manager(int keycode, t_main *main)
{
        if (keycode == 53 || keycode == 65307)
                close_window(main);
	if (keycode == 122 || keycode == 65362) // Z
	{
		update_player_pos(main, 'Z');
	}
	if (keycode == 113 || keycode == 65361) // Q
	{
		update_player_pos(main, 'Q');
	}
	if (keycode == 115 || keycode == 65364) // S
	{
		update_player_pos(main, 'S');
	}
	if (keycode == 100 || keycode == 65363) // D
	{
		update_player_pos(main, 'D');
	}
        return (0);
}

void    free_rest(t_main *main)
{
        int     i;

        i = 0;
        while (main->map.grid[i] != NULL)
        {
                free(main->map.grid[i]);
                i++;
        }
        free(main->map.grid);
}

void	put_background(t_main *main)
{
	int	i = 0;
	int	j = 0;
	int	px_w = 0;
	int	px_h = 0;
	
	while (main->map.grid[i] != NULL)
	{
        	while (main->map.grid[i][j] != '\0')
        	{
			if (main->map.grid[i][j] == '1')
				mlx_put_image_to_window(main->mlx_ptr, main->mlx_win, main->spr_wall.img, px_w, px_h);
			if (main->map.grid[i][j] == '0')
				mlx_put_image_to_window(main->mlx_ptr, main->mlx_win, main->spr_floor.img, px_w, px_h);
			if (main->map.grid[i][j] == 'P')
				mlx_put_image_to_window(main->mlx_ptr, main->mlx_win, main->spr_player_front.img, px_w, px_h);
			if (main->map.grid[i][j] == 'C')
				mlx_put_image_to_window(main->mlx_ptr, main->mlx_win, main->spr_floor_coll.img, px_w, px_h);
			if (main->map.grid[i][j] == 'E')
				mlx_put_image_to_window(main->mlx_ptr, main->mlx_win, main->spr_door_close.img, px_w, px_h);
			if (main->map.player_on_exit == 1)
			{
				free_rest(main);
				exit (ft_printf("YOU WON THE GAME GG !!!\n"));
			}
			j++;
			px_w += 48;
        	}
		i++;
		px_h += 48;
		j = 0;
		px_w = 0;
	}
}

int	game_refresh(t_main *main)
{
	put_background(main);
	return (0);
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
	grid_init(&main);
	check_walls1(&main.map);
	check_walls2(&main.map);
	check_epc(&main.map, &main.p_pos, &main.e_pos);
	check_path(&main.map, main.p_pos.x, main.p_pos.y);
	main.map.grid[main.e_pos.y][main.e_pos.x] = '0';
	free_what_to_free(&main);
	ft_printf("exit found : %d\n", main.map.exit_acc); // à enlever
	ft_printf("collectibles found : %d\n", main.map.coll_acc); // à enlever
	if (main.map.exit_acc != 1 || main.map.coll_acc != main.map.Coll)
		return (ft_printf("Your map is invalid because the exit or collectibles aren't accessible.\n"));
	main.mlx_ptr = mlx_init();
	main.mlx_win = mlx_new_window(main.mlx_ptr, main.map.width * 48, main.map.height * 50, "so_long");
	main.img = mlx_new_image(main.mlx_ptr, main.map.width * 48, main.map.height * 50);
	main.addr = mlx_get_data_addr(main.img, &main.bpp, &main.line_size, &main.endian);
	sprites_init(&main);
	mlx_hook(main.mlx_win, 2, 1L<<0, key_manager, &main);
	mlx_hook(main.mlx_win, 17, 0, close_window, &main);
	//put_background(&main);
	
	//mlx_put_image_to_window(main.mlx_ptr, main.mlx_win, main.spr_player_front.img, 0, 0);
	mlx_loop_hook(main.mlx_ptr, game_refresh, &main);
	mlx_loop(main.mlx_ptr);
	return (0);
}
