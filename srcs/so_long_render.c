#include "../includes/so_long.h"

int	game_refresh(t_main *main)
{
	put_background(main);
	return (0);
}

void	put_background(t_main *main)
{
	int	i = 0;
	int	j = 0;
	int	px_w = 0;
	int	px_h = 0;
	
	while (i < main->map.height)
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
				mlx_destroy_image(main->mlx_ptr, main->spr_wall.img);
				mlx_destroy_image(main->mlx_ptr, main->spr_floor.img);
				mlx_destroy_image(main->mlx_ptr, main->spr_floor_coll.img);
				mlx_destroy_image(main->mlx_ptr, main->spr_door_close.img);
				mlx_destroy_image(main->mlx_ptr, main->spr_player_front.img);
				mlx_destroy_image(main->mlx_ptr, main->img);
				mlx_destroy_window(main->mlx_ptr, main->mlx_win);
				mlx_destroy_display(main->mlx_ptr);
				free(main->mlx_ptr);
				free_grids(&main->map);
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