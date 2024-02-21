/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 16:14:23 by jtu               #+#    #+#             */
/*   Updated: 2024/02/21 14:16:25 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft/libft.h"
# include "libft/get_next_line/get_next_line_bonus.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <fcntl.h>

typedef enum s_drc
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NUM_DRC
}	t_drc;

typedef enum s_block
{
	START,
	GRASS,
	WALL,
	COLLECTIBLE,
	ENEMY,
	EXIT_OPEN,
	EXIT_CLOSED,
	PLAYER_STAND,
	PLAYER_UP,
	PLAYER_DOWN,
	PLAYER_LEFT,
	PLAYER_RIGHT,
	PLAYER_FAIL,
	NUM_BLOCK_TYPES
}	t_block;

typedef enum status
{
	PLAYING,
	FAILED,
	WON
}	t_status;

typedef struct s_crd
{
	int32_t	x;
	int32_t	y;
}	t_crd;

typedef struct s_game
{
	char		**map;
	int32_t		width;
	int32_t		height;
	int			collectible;
	int			enemy;
	int			player;
	int			exit;
	int			moves;
	int			collected;
	mlx_t		*mlx;
	mlx_image_t	*img_set[NUM_BLOCK_TYPES];
	mlx_image_t	*counts;
	t_status	status;
	t_crd		player_crd;
	t_crd		exit_crd;
}	t_game;

# define PIXELS 16

// Errors handling
void	error_exit(char *msg);
void	delete_map(char **map, int32_t height);

// Map Reading
void	read_map(t_game *game, char *file);

// Map validation
void	check_char(int c);
void	check_file(char *file);
void	check_map(t_game *game);
void	get_crd(t_game *game);

// Display game
void	init_img(t_game *game);
void	display_img(t_game *game);

// Play game
void	move_hook(mlx_key_data_t keydata, void *param);
void	clear_player(t_game *game);
void	move_enemy(void *param);
char	get_next_block(t_game *game, t_drc direction);
void	collect_points(t_game *game, int32_t x, int32_t y);

// End game
void	check_enemy(t_game *game);
void	check_status(t_game *game);
void	end_game(mlx_key_data_t keydata, void *param);

#endif
