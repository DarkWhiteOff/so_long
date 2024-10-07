#include "../includes/so_long.h"

void	save_pos(t_pxy *x_pos, int j, int i)
{
	x_pos->x = j;
	x_pos->y = i;
}

void	check_fd_error(t_main *main)
{
	if (main->map.fd < 0 || read(main->map.fd, 0, 0) < 0)
		exit (ft_printf("Error\nfd not working."));
}