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
