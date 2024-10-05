/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_player_pos.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:09:22 by zamgar            #+#    #+#             */
/*   Updated: 2024/10/04 20:09:23 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	check_map_limits_epc(t_map *map, int y, int x, int check)
{
	if (check == 0)
	{
		if (map->grid[y][x] == '1' || map->highlight_grid[y][x] == '1'
			|| x < 0 || y < 0 || x > map->w || y > map->h)
			return (0);
	}
	else if (check == 1)
	{
		if (map->grid[y][x] != 'E' && map->grid[y][x] != 'P' && map->grid[y][x]
			!= 'C' && map->grid[y][x] != '0' && map->grid[y][x] != '1')
			return (0);
	}
	return (1);
}

void	actualise_map_data(t_main *main)
{
	int	x;
	int	y;

	x = main->p_pos.x;
	y = main->p_pos.y;
	if (main->map.grid[y][x] == 'C')
		main->map.coll--;
	if (main->map.coll == 0)
		main->map.grid[main->e_pos.y][main->e_pos.x] = 'E';
	main->map.grid[y][x] = 'P';
	if (main->map.grid[main->e_pos.y][main->e_pos.x] == 'P'
		&& main->map.coll == 0)
		main->map.player_on_exit = 1;
}

void	update_player_pos(t_main *main, char c)
{
	main->map.grid[main->p_pos.y][main->p_pos.x] = '0';
	if (c == 'Z' && main->map.grid[main->p_pos.y - 1][main->p_pos.x] != '1')
	{
		main->p_pos.y = main->p_pos.y - 1;
		ft_printf("Moves : %d\n", ++main->map.moves);
	}
	if (c == 'Q' && main->map.grid[main->p_pos.y][main->p_pos.x - 1] != '1')
	{
		main->p_pos.x = main->p_pos.x - 1;
		ft_printf("Moves : %d\n", ++main->map.moves);
	}
	if (c == 'S' && main->map.grid[main->p_pos.y + 1][main->p_pos.x] != '1')
	{
		main->p_pos.y = main->p_pos.y + 1;
		ft_printf("Moves : %d\n", ++main->map.moves);
	}
	if (c == 'D' && main->map.grid[main->p_pos.y][main->p_pos.x + 1] != '1')
	{
		main->p_pos.x = main->p_pos.x + 1;
		ft_printf("Moves : %d\n", ++main->map.moves);
	}
	actualise_map_data(main);
}
