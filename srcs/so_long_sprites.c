#include "../includes/so_long.h"

void	free_sprites(t_main *main)
{
	if (main->spr_player_front.img)
		mlx_destroy_image(main->mlx_ptr, main->spr_player_front.img);
	if (main->spr_wall.img)
		mlx_destroy_image(main->mlx_ptr, main->spr_wall.img);
	if (main->spr_floor.img)
		mlx_destroy_image(main->mlx_ptr, main->spr_floor.img);
	if (main->spr_floor_coll.img)
		mlx_destroy_image(main->mlx_ptr, main->spr_floor_coll.img);
	if (main->spr_door_close.img)
		mlx_destroy_image(main->mlx_ptr, main->spr_door_close.img);
	mlx_destroy_image(main->mlx_ptr, main->img);
	mlx_destroy_window(main->mlx_ptr, main->mlx_win);
	mlx_destroy_display(main->mlx_ptr);
	free(main->mlx_ptr);
	free_grids(&main->map);
}

void	sprites_init(t_main *main)
{
	main->spr_wall.img = mlx_xpm_file_to_image(main->mlx_ptr, "sprites_tiles/spr_wall.xpm", &main->spr_wall.width, &main->spr_wall.height);
	main->spr_floor.img = mlx_xpm_file_to_image(main->mlx_ptr, "sprites_tiles/spr_floor.xpm", &main->spr_floor.width, &main->spr_floor.height);
	main->spr_floor_coll.img = mlx_xpm_file_to_image(main->mlx_ptr, "sprites_tiles/spr_floor_coll.xpm", &main->spr_floor_coll.width, &main->spr_floor_coll.height);
	main->spr_door_close.img = mlx_xpm_file_to_image(main->mlx_ptr, "sprites_tiles/spr_door_close.xpm", &main->spr_door_close.width, &main->spr_door_close.height);
	main->spr_player_front.img = mlx_xpm_file_to_image(main->mlx_ptr, "sprites_tiles/spr_player_front.xpm", &main->spr_player_front.width, &main->spr_player_front.height);
	if (!main->spr_player_front.img || !main->spr_wall.img || !main->spr_floor.img || !main->spr_floor_coll.img || !main->spr_door_close.img)
	{
		free_sprites(main);
		exit(ft_printf("Error\nSprites init FAILED"));
	}
}