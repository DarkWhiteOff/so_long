/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zamgar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:22:55 by zamgar            #+#    #+#             */
/*   Updated: 2024/10/04 19:22:57 by zamgar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_grids(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->h)
	{
		free(map->grid[i]);
		free(map->highlight_grid[i]);
		i++;
	}
	free(map->grid);
	free(map->highlight_grid);
}

int	check_map_name(char *map_name)
{
	int	i;
	int slash;

	i = 0;
	while (map_name[i] != '\0')
		i++;
	if (map_name[i - 1] == 'r' && map_name[i - 2] == 'e'
		&& map_name[i - 3] == 'b' && map_name[i - 4] == '.'
			&& (map_name[i - 5] != '/' && map_name[i - 5] != 0))
		return (0);
	return (1);
}

void	get_screen_size(t_map *map)
{
	void	*mlxptr;

	mlxptr = mlx_init();
	if (!mlxptr)
	{
		free(mlxptr);
		exit (ft_printf("Error\nMlx failed.\n"));
	}
	mlx_get_screen_size(mlxptr, &map->sc_s.x, &map->sc_s.y);
	mlx_destroy_display(mlxptr);
	free(mlxptr);
}

size_t	strlenmap(char *line, t_map *map)
{
	int	i;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (i > map->sc_s.x / 48)
	{
		free(line);
		exit (ft_printf("Error\nYour screen is too small for this map !"));
	}
	return (i);
}

int	close_window(t_main *main)
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
	exit (ft_printf("Windows was killed.\n"));
}
