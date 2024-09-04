#ifndef SO_LONG_H
# define SO_LONG_H

#include "mlx_linux/mlx.h"
#include "get_next_line/get_next_line.h"
#include "ft_printf/ft_printf.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

typedef struct s_pxy {
	int	x;
	int	y;
}	t_pxy;

typedef struct s_sprite {
	int		width;
	int		height;
	void	*img;
}	t_sprite;


typedef struct s_map {
    char    *path;
    size_t  height;
    size_t  width;
	size_t	Ex;
	size_t	Pos;
	size_t	Coll;
	int		fd;
	char	**grid;
	char	**highlight_grid;
	size_t	exit_acc;
	size_t	coll_acc;
	size_t	player_on_exit;
	size_t	moves;
	t_pxy		screen_size;
}	t_map;

typedef struct s_main {
	void		*mlx_ptr;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bpp;
	int			line_size;
	int			endian;
	t_map		map;
	t_pxy		p_pos;
	t_pxy		e_pos;
	t_sprite	spr_wall;
	t_sprite	spr_floor;
	t_sprite	spr_coll1;
	t_sprite	spr_coll2;
	t_sprite	spr_floor_coll;
	t_sprite	spr_door_close;
	t_sprite	spr_door_open;
	t_sprite	spr_player_front;
	t_sprite	spr_player_back;
	t_sprite	spr_player_side;
	t_sprite	spr_you_win;
}	t_main;

void	free_grids(t_map *map);
int     check_map_name(char *map_name);
void    vars_init(t_map *map, char *map_path);
size_t  ft_strlenmap(char *line, t_map *map);
void    parse_map(t_map *map, t_pxy *p_pos);
void    allocate_grids(t_map *map);
void    grid_init(t_main *main);
void    check_walls1(t_map *map);
void    check_walls2(t_map *map);
void    check_epc(t_map *map, t_pxy *p_pos, t_pxy *e_pos);
void    check_path(t_map *map, size_t x, size_t y);
void	free_sprites(t_main *main);
void	sprites_init(t_main *main);
int     close_window(t_main *main);
void    actualise_map_data(t_main *main);
void	update_player_pos(t_main *main, char c);
int     key_manager(int keycode, t_main *main);
void	put_background(t_main *main);
int	game_refresh(t_main *main);
void	get_screen_size(t_map *map);
void	checks_inits(t_main *main);
void	render_init(t_main *main);

#endif
