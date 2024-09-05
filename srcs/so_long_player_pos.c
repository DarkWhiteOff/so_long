#include "../includes/so_long.h"

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
}

void	update_player_pos(t_main *main, char c)
{
	main->map.grid[main->p_pos.y][main->p_pos.x] = '0';
	if (c == 'Z' && main->map.grid[main->p_pos.y - 1][main->p_pos.x] != '1')
	{
		main->p_pos.y = main->p_pos.y - 1;
		main->map.moves++;
		ft_printf("Moves : %d\n", main->map.moves);
	}
	if (c == 'Q' && main->map.grid[main->p_pos.y][main->p_pos.x - 1] != '1')
	{
		main->p_pos.x = main->p_pos.x - 1;
		main->map.moves++;
		ft_printf("Moves : %d\n", main->map.moves);
	}
	if (c == 'S' && main->map.grid[main->p_pos.y + 1][main->p_pos.x] != '1')
	{
		main->p_pos.y = main->p_pos.y + 1;
		main->map.moves++;
		ft_printf("Moves : %d\n", main->map.moves);
	}
	if (c == 'D' && main->map.grid[main->p_pos.y][main->p_pos.x + 1] != '1')
	{
		main->p_pos.x = main->p_pos.x + 1;
		main->map.moves++;
		ft_printf("Moves : %d\n", main->map.moves);
	}
	actualise_map_data(main);
}