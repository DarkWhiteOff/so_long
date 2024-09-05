#include "../includes/so_long.h"

int     key_manager(int keycode, t_main *main)
{
    if (keycode == 53 || keycode == 65307)
        close_window(main);
	if (keycode == 122 || keycode == 65362) // Z
		update_player_pos(main, 'Z');
	if (keycode == 113 || keycode == 65361) // Q
		update_player_pos(main, 'Q');
	if (keycode == 115 || keycode == 65364) // S
		update_player_pos(main, 'S');
	if (keycode == 100 || keycode == 65363) // D
		update_player_pos(main, 'D');
    return (0);
}

void    vars_init(t_map *map, char *map_path)
{
    map->path = map_path;
    map->height = 0;
    map->width = 0;
    map->Ex = 0;
    map->Pos = 0;
    map->Coll = 0;
    map->exit_acc = 0;
    map->coll_acc = 0;
	map->player_on_exit = 0;
	map->moves = 0;
	map->screen_size.x = 0;
	map->screen_size.y = 0;
}

void	checks_inits(t_main *main)
{
	get_screen_size(&main->map);
	parse_map(&main->map, &main->p_pos);
	grid_init(main);
	check_walls1(&main->map);
	check_walls2(&main->map);
	check_epc(&main->map, &main->p_pos, &main->e_pos);
	check_path(&main->map, main->p_pos.x, main->p_pos.y);
	main->map.grid[main->e_pos.y][main->e_pos.x] = '0';
	if (main->map.exit_acc != 1 || main->map.coll_acc != main->map.Coll)
	{
		free_grids(&main->map);
		exit (ft_printf("Error\nYour map is invalid because the exit or collectibles aren't accessible.\n"));
	}
}

void	render_init(t_main *main)
{
	main->mlx_ptr = mlx_init();
	if (!main->mlx_ptr)
	{
		free(main->mlx_ptr);
		exit (ft_printf("Error\nMlx failed.\n"));
	}
	main->mlx_win = mlx_new_window(main->mlx_ptr, main->map.width * 48, main->map.height * 48, "so_long");
	if (!main->mlx_win)
	{
		mlx_destroy_display(main->mlx_ptr);
		free(main->mlx_ptr);
		free_grids(&main->map);
		exit (ft_printf("Error\nMlx failed.\n"));
	}
	main->img = mlx_new_image(main->mlx_ptr, main->map.width * 48, main->map.height * 48);
	if (!main->img)
	{
		mlx_destroy_window(main->mlx_ptr, main->mlx_win);
		mlx_destroy_display(main->mlx_ptr);
		free(main->mlx_ptr);
		free_grids(&main->map);
		exit (ft_printf("Error\nMlx failed.\n"));
	}
	main->addr = mlx_get_data_addr(main->img, &main->bpp, &main->line_size, &main->endian);
}

int	main(int argc, char *argv[])
{
	t_main main;

	if (argc != 2)
		return (ft_printf("Error\nNo map file was entered or to much files were entered.\n"));
	if (check_map_name(argv[1]) == 1)
		return (ft_printf("Error\nMap name is incorrect.\n"));
	vars_init(&main.map, argv[1]);
	checks_inits(&main);
	render_init(&main);
	sprites_init(&main);
	mlx_hook(main.mlx_win, 2, 1L<<0, key_manager, &main);
	mlx_hook(main.mlx_win, 17, 0, close_window, &main);
	mlx_loop_hook(main.mlx_ptr, game_refresh, &main);
	mlx_loop(main.mlx_ptr);
	return (0);
}