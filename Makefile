NAME = so_long

LIBFT_PATH = ./libft/
LIBFT_NAME = libft.a
LIBFT_LIB = $(addprefix $(LIBFT_PATH), $(LIBFT_NAME))

SRC = srcs/so_long.c srcs/so_long_checks1.c srcs/so_long_checks2.c srcs/so_long_player_pos.c srcs/so_long_render.c srcs/so_long_utils.c srcs/so_long_sprites.c

OBJS := $(SRC:%.c=%.o)

CC = gcc
FLAGS = -Wall -Wextra -Werror -g -g3

.c.o:
	$(CC) $(FLAGS) -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11 -c $< -o $@

all: $(NAME)

$(LIBFT_LIB):
	make -sC $(LIBFT_PATH)

$(NAME) : $(LIBFT_LIB) $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBFT_LIB) -Lmlx_linux -lmlx_Linux -Imlx_linux -lXext -lX11 -o $(NAME)

clean:
	make clean -sC $(LIBFT_PATH)
	rm -rf $(OBJS)

fclean: clean
	make fclean -sC $(LIBFT_PATH)
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re