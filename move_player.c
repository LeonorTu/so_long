/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:47:07 by jtu               #+#    #+#             */
/*   Updated: 2024/02/21 12:53:59 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	move_player(t_game *game, t_drc direction)
{
	if (direction == UP)
	{
		game->img_set[PLAYER_UP]->enabled = true;
		game->player_crd.y--;
	}
	else if (direction == DOWN)
	{
		game->img_set[PLAYER_DOWN]->enabled = true;
		game->player_crd.y++;
	}
	else if (direction == LEFT)
	{
		game->img_set[PLAYER_LEFT]->enabled = true;
		game->player_crd.x--;
	}
	else if (direction == RIGHT)
	{
		game->img_set[PLAYER_RIGHT]->enabled = true;
		game->player_crd.x++;
	}
	game->moves++;
}

static void	move_img(t_game *game)
{
	game->img_set[PLAYER_UP]->instances[0].x = game->player_crd.x * PIXELS;
	game->img_set[PLAYER_UP]->instances[0].y = game->player_crd.y * PIXELS;
	game->img_set[PLAYER_DOWN]->instances[0].x = game->player_crd.x * PIXELS;
	game->img_set[PLAYER_DOWN]->instances[0].y = game->player_crd.y * PIXELS;
	game->img_set[PLAYER_LEFT]->instances[0].x = game->player_crd.x * PIXELS;
	game->img_set[PLAYER_LEFT]->instances[0].y = game->player_crd.y * PIXELS;
	game->img_set[PLAYER_RIGHT]->instances[0].x = game->player_crd.x * PIXELS;
	game->img_set[PLAYER_RIGHT]->instances[0].y = game->player_crd.y * PIXELS;
	game->img_set[PLAYER_FAIL]->instances[0].x = game->player_crd.x * PIXELS;
	game->img_set[PLAYER_FAIL]->instances[0].y = game->player_crd.y * PIXELS;
}

static void	move(t_game *game, t_drc direction)
{
	char	next_block;
	char	*moves;

	next_block = get_next_block(game, direction);
	if (next_block != '1' && next_block != 'E')
	{
		clear_player(game);
		move_player(game, direction);
		if (next_block == 'C')
			collect_points(game, game->player_crd.x, game->player_crd.y);
		move_img(game);
	}
	mlx_delete_image(game->mlx, game->counts);
	moves = ft_itoa(game->moves);
	game->counts = mlx_put_string(game->mlx, moves, \
	(game->width + 2) * PIXELS / 2, 0);
	free(moves);
	check_status(game);
}

void	move_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *) param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(game->mlx);
	else if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP) && \
	keydata.action == MLX_PRESS)
		move(game, UP);
	else if ((keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN) && \
	keydata.action == MLX_PRESS)
		move(game, DOWN);
	else if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT) && \
	keydata.action == MLX_PRESS)
		move(game, LEFT);
	else if ((keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT) && \
	keydata.action == MLX_PRESS)
		move(game, RIGHT);
}
