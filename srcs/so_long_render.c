/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:54:12 by zamgar            #+#    #+#             */
/*   Updated: 2024/10/04 19:54:26 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	game_refresh(t_main *main)
{
	int	i;
	int	j;
	int	px_w;
	int	px_h;

	i = 0;
	j = 0;
	px_w = 0;
	px_h = 0;
	while (i < main->map.h)
	{
		update_map(main, i, px_h);
		if (main->map.player_on_exit == 1)
			player_wins(main);
		i++;
		px_h += 48;
	}
	return (0);
}

void	update_map(t_main *main, int i, int px_h)
{
	int	j;
	int	px_w;

	j = 0;
	px_w = 0;
	while (main->map.grid[i][j] != '\0')
	{
		if (main->map.grid[i][j] == '1')
			mlx_put_image_to_window(main->mlx_p,
				main->mlx_win, main->spr_wall.img, px_w, px_h);
		if (main->map.grid[i][j] == '0')
			mlx_put_image_to_window(main->mlx_p,
				main->mlx_win, main->spr_floor.img, px_w, px_h);
		if (main->map.grid[i][j] == 'P')
			mlx_put_image_to_window(main->mlx_p,
				main->mlx_win, main->spr_p.img, px_w, px_h);
		if (main->map.grid[i][j] == 'C')
			mlx_put_image_to_window(main->mlx_p,
				main->mlx_win, main->spr_coll.img, px_w, px_h);
		if (main->map.grid[i][j] == 'E')
			mlx_put_image_to_window(main->mlx_p,
				main->mlx_win, main->spr_door.img, px_w, px_h);
		j++;
		px_w += 48;
	}
}

void	player_wins(t_main *main)
{
	mlx_destroy_image(main->mlx_p, main->spr_wall.img);
	mlx_destroy_image(main->mlx_p, main->spr_floor.img);
	mlx_destroy_image(main->mlx_p, main->spr_coll.img);
	mlx_destroy_image(main->mlx_p, main->spr_door.img);
	mlx_destroy_image(main->mlx_p, main->spr_p.img);
	mlx_destroy_image(main->mlx_p, main->img);
	mlx_destroy_window(main->mlx_p, main->mlx_win);
	mlx_destroy_display(main->mlx_p);
	free(main->mlx_p);
	free_grids(&main->map);
	exit (ft_printf("YOU WON THE GAME GG !!!\n"));
}
