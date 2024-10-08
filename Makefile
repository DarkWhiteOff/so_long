NAME = so_long

LIBFT_PATH = ./libft/
LIBFT_NAME = libft.a
LIBFT_LIB = $(addprefix $(LIBFT_PATH), $(LIBFT_NAME))

MLX_PATH = ./mlx/
MLX_LIB = $(addprefix $(MLX_PATH), $(MLX_NAME))

SRC = srcs/so_long.c srcs/so_long_checks1.c srcs/so_long_checks2.c srcs/so_long_player_pos.c srcs/so_long_render.c srcs/so_long_utils.c srcs/so_long_utils2.c srcs/so_long_sprites.c

OBJS := $(SRC:%.c=%.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror -g -g3
MLX_FLAGS = -Lmlx -lmlx_Linux -Imlx -lXext -lX11

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(LIBFT_LIB):
	make -sC $(LIBFT_PATH)

$(NAME) : $(LIBFT_LIB) $(OBJS)
	make -sC $(MLX_PATH)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME) -L$(MLX_PATH) $(MLX_FLAGS)

clean:
	make clean -sC $(LIBFT_PATH)
	make clean -sC $(MLX_PATH)
	rm -rf $(OBJS)

fclean: clean
	make fclean -sC $(LIBFT_PATH)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re