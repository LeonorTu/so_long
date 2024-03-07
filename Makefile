NAME = so_long

LIBFT = ./libft/libft.a

MLX42 = ./MLX42/build/libmlx42.a

SRCS = so_long.c \
	read_map.c \
	map_validation.c \
	map_utils.c \
	load_img.c \
	display_img.c \
	error_handler.c \
	move_player.c \
	move_enemy.c \
	move_utils.c \
	end_game.c

CFLAGS = -Wall -Wextra -Werror

MLX42FLAGS = -Iinclude -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

all: ${NAME}

${NAME}: ${SRCS} $(LIBFT) $(MLX42)
	@cc $(CFLAGS) $^ -o $@ $(LIBFT) $(MLX42) $(MLX42FLAGS)

$(LIBFT):
	@make -C libft/

$(MLX42):
	@cd MLX42 && cmake -B build
	@cd MLX42 && cmake --build build -j4
	@make -C MLX42/build -j4

clean:
	@make clean -C libft
	@make clean -C MLX42/build
	@rm -rf *.dSYM
	@rm -rf .vscode
	@rm -rf .DS_Store

fclean: clean
	@rm -f ${NAME} ${NAME_BONUS}
	@rm -rf MLX42/build
	@make fclean -C libft

re: fclean all

.PHONY: all clean fclean re
