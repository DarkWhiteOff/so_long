/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:07:17 by zamgar            #+#    #+#             */
/*   Updated: 2024/10/04 19:07:18 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	key_manager(int keycode, t_main *main)
{
	if (keycode == 53 || keycode == 65307)
		close_window(main);
	if (keycode == 119)
		update_player_pos(main, 'Z');
	if (keycode == 97)
		update_player_pos(main, 'Q');
	if (keycode == 115)
		update_player_pos(main, 'S');
	if (keycode == 100)
		update_player_pos(main, 'D');
	return (0);
}

void	vars_init(t_map *map, char *map_path)
{
	map->path = map_path;
	map->h = 0;
	map->w = 0;
	map->ex = 0;
	map->pos = 0;
	map->coll = 0;
	map->exit_acc = 0;
	map->coll_acc = 0;
	map->player_on_exit = 0;
	map->moves = 0;
	map->sc_s.x = 0;
	map->sc_s.y = 0;
}

void	checks_inits(t_main *main)
{
	get_screen_size(&main->map);
	parse_map(&main->map);
	grid_init(main);
	check_walls1(&main->map);
	check_walls2(&main->map);
	check_epc(&main->map, &main->p_pos);
	check_path(&main->map, main->p_pos.x, main->p_pos.y);
	main->map.grid[main->e_pos.y][main->e_pos.x] = '0';
	if (main->map.exit_acc != 1 || main->map.coll_acc != main->map.coll)
	{
		free_grids(&main->map);
		exit (ft_printf("Error\nExit or collectibles aren't accessible.\n"));
	}
}

void	render_init(t_main *main)
{
	main->mlx_p = mlx_init();
	if (!main->mlx_p)
	{
		free(main->mlx_p);
		exit (ft_printf("Error\nMlx failed.\n"));
	}
	main->mlx_win = mlx_new_window(main->mlx_p,
			main->map.w * 48, main->map.h * 48, "so_long");
	if (!main->mlx_win)
	{
		mlx_destroy_display(main->mlx_p);
		free(main->mlx_p);
		free_grids(&main->map);
		exit (ft_printf("Error\nMlx failed.\n"));
	}
	main->img = mlx_new_image(main->mlx_p, main->map.w * 48, main->map.h * 48);
	if (!main->img)
	{
		mlx_destroy_window(main->mlx_p, main->mlx_win);
		mlx_destroy_display(main->mlx_p);
		free(main->mlx_p);
		free_grids(&main->map);
		exit (ft_printf("Error\nMlx failed.\n"));
	}
	main->addr = mlx_get_data_addr(main->img, &main->b, &main->ls, &main->end);
}

int	main(int argc, char *argv[])
{
	t_main	main;

	if (argc != 2)
		return (ft_printf("Error\nNo map file /to much files were entered.\n"));
	if (check_map_name(argv[1]) == 1)
		return (ft_printf("Error\nMap name is incorrect.\n"));
	vars_init(&main.map, argv[1]);
	checks_inits(&main);
	render_init(&main);
	sprites_init(&main);
	mlx_hook(main.mlx_win, 2, 1L << 0, key_manager, &main);
	mlx_hook(main.mlx_win, 17, 0, close_window, &main);
	mlx_loop_hook(main.mlx_p, game_refresh, &main);
	mlx_loop(main.mlx_p);
	return (0);
}
