#include "mlx_linux/mlx.h"
#include <stdio.h>

typedef struct	s_data {
        void    *img;
        char    *addr;
        int             bits_per_pixel;
        int             line_length;
        int             endian;
}	t_data;

typedef struct s_main	{
	void	*mlx_ptr;
	void	*mlx_win;
}	t_main;

void    my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
        char    *dst;

        dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
}

void    draw_pixel_square(t_data *data, int x, int y, int square_length, int color)
{
        int     i = x;
        int     j = y;

        while (i < x + square_length && j < y + square_length)
        {
                my_mlx_pixel_put(data, i, y, color);
                my_mlx_pixel_put(data, i, (y + 100), color);
                my_mlx_pixel_put(data, x, j, color);
                my_mlx_pixel_put(data, (x + 100), j, color);
                i++;
                j++;
        }
}

int	close_window(t_main *main)
{
	mlx_destroy_window(main->mlx_ptr, main->mlx_win);
	return (0);
}

int	print_keycode(int keycode)
{
	printf("%d\n", keycode);
	return (0);
}

int	key_manager(int keycode, t_main *main)
{
	if (keycode == 53 || keycode == 65307)
		close_window(main);
	return (0);
}

int     main(void)
{
        t_main	main;
        t_data  img;

        main.mlx_ptr = mlx_init();

        main.mlx_win = mlx_new_window(main.mlx_ptr, 960, 540, "Hello World!");
        img.img = mlx_new_image(main.mlx_ptr, 960, 540);
        img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

        draw_pixel_square(&img, 480, 270, 100, 0x00FF0000);
        mlx_put_image_to_window(main.mlx_ptr, main.mlx_win, img.img, 0, 0);
	
	mlx_hook(main.mlx_win, 2, 1L<<0, key_manager, &main);
	mlx_hook(main.mlx_win, 17, 0, close_window, &main);
	mlx_key_hook(main.mlx_win, print_keycode, &main);
        mlx_loop(main.mlx_ptr);
	return (0);
}
