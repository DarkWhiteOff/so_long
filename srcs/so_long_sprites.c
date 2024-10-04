/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_sprites.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:26:18 by zamgar            #+#    #+#             */
/*   Updated: 2024/10/04 19:26:19 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_sprites(t_main *main)
{
	if (main->spr_p.img)
		mlx_destroy_image(main->mlx_p, main->spr_p.img);
	if (main->spr_wall.img)
		mlx_destroy_image(main->mlx_p, main->spr_wall.img);
	if (main->spr_floor.img)
		mlx_destroy_image(main->mlx_p, main->spr_floor.img);
	if (main->spr_coll.img)
		mlx_destroy_image(main->mlx_p, main->spr_coll.img);
	if (main->spr_door.img)
		mlx_destroy_image(main->mlx_p, main->spr_door.img);
	mlx_destroy_image(main->mlx_p, main->img);
	mlx_destroy_window(main->mlx_p, main->mlx_win);
	mlx_destroy_display(main->mlx_p);
	free(main->mlx_p);
	free_grids(&main->map);
}

void	sprites_init(t_main *main)
{
	main->spr_wall.img = mlx_xpm_file_to_image(main->mlx_p,
			"spr_tiles/spr_wall.xpm", &main->spr_wall.w, &main->spr_wall.h);
	main->spr_floor.img = mlx_xpm_file_to_image(main->mlx_p,
			"spr_tiles/spr_floor.xpm", &main->spr_floor.w, &main->spr_floor.h);
	main->spr_coll.img = mlx_xpm_file_to_image(main->mlx_p,
			"spr_tiles/spr_coll.xpm", &main->spr_coll.w, &main->spr_coll.h);
	main->spr_door.img = mlx_xpm_file_to_image(main->mlx_p,
			"spr_tiles/spr_door.xpm", &main->spr_door.w, &main->spr_door.h);
	main->spr_p.img = mlx_xpm_file_to_image(main->mlx_p,
			"spr_tiles/spr_player.xpm", &main->spr_p.w, &main->spr_p.h);
	if (!main->spr_p.img || !main->spr_wall.img
		|| !main->spr_floor.img || !main->spr_coll.img || !main->spr_door.img)
	{
		free_sprites(main);
		exit(ft_printf("Error\nSprites init FAILED"));
	}
}
