NAME = so_long

SRC = srcs/so_long.c srcs/so_long_checks1.c srcs/so_long_checks2.c srcs/so_long_player_pos.c srcs/so_long_render.c srcs/so_long_utils.c srcs/so_long_sprites.c
GNL_SRC = get_next_line/get_next_line.c  get_next_line/get_next_line_utils.c
PRINTF_SRC = ft_printf/ft_printf.c ft_printf/ft_hex.c ft_printf/ft_ptr.c ft_printf/ft_putcharstr.c ft_printf/ft_itoa.c ft_printf/ft_unsigned_itoa.c

OBJS := $(SRC:%.c=%.o)
GNL_OBJS := $(GNL_SRC:%.c=%.o)
PRINTF_OBJS := $(PRINTF_SRC:%.c=%.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror -g -g3

all: $(NAME)

$(NAME) : $(OBJS) $(GNL_OBJS) $(PRINTF_OBJS)
	$(CC) $(FLAGS) $(OBJS) $(GNL_OBJS) $(PRINTF_OBJS) -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11 -o $(NAME)

clean:
	rm -rf $(OBJS) $(GNL_OBJS) $(PRINTF_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
