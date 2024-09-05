#ifndef SO_LONG_H
# define SO_LONG_H

# include "../mlx_linux/mlx.h"
# include "struct.h"

// So long

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
//int	main(int argc, char *argv[]);

// Get next line

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char				*get_next_line(int fd, t_map *map);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strcat(char *dest, char *src);
char				*ft_strchr(const char *s, int c);
int					ftft_strlen(const char *s, unsigned char c);
char				*ft_strdup(const char *s);
size_t				ft_strlen(const char *s);
char				*ft_substr(char const *str, unsigned int start, size_t len);
char				*ft_gen(char *newstr, char const *str,
						unsigned int s, size_t len);
size_t				ft_calc(char const *str, unsigned int start, size_t len);

// Ft printf

int					ft_printf(const char *str, ...);
int					get_next_arg(va_list *ap, char c);
int					ft_putchar(char c);
int					ft_itoa2(int n);
char				*ft_itoa(int n);
int					ft_count(int n);
char				*ft_min(char *str);
int					ft_putstr(char *str);
//pas utilisée
int					ft_dec_into_hex(unsigned int n, int b);
void				ft_print_array(char *array, int i);
char				*ft_fill_hexarray(unsigned int n, char *string,
						char *array);
int					ft_get_size_hexarray(unsigned int n);
int					ft_unsigned_itoa2(unsigned int n);
char				*ft_unsigned_itoa(unsigned int n);
int					ft_unsigned_count(unsigned int n);
int					ft_putptr(unsigned long long adress);
char				*ft_fill_ptrarray(unsigned long long adress,
						char *string, char *array);
int					ft_get_size_ptrarray(unsigned long long adress);
int					ft_putstr(char *str);

#endif
