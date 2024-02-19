/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 17:47:07 by jtu               #+#    #+#             */
/*   Updated: 2024/02/19 16:59:39 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_player(t_game *game, t_drc direction)
{
	if (direction == UP)
	{
		game->img_set[PLAYER_UP]->enabled = true;
		game->player.y--;
	}
	else if (direction == DOWN)
	{
		game->img_set[PLAYER_DOWN]->enabled = true;
		game->player.y++;
	}
	else if (direction == LEFT)
	{
		game->img_set[PLAYER_LEFT]->enabled = true;
		game->player.x--;
	}
	else if (direction == RIGHT)
	{
		game->img_set[PLAYER_RIGHT]->enabled = true;
		game->player.x++;
	}
	game->moves++;
}

void	end_game(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *) param;

	if (game->status == FAILED)
		mlx_put_string(game->mlx, "YOU LOST :(", (game->width - 7) * PIXELS / 2, (game->height - 2)* PIXELS / 2);
	else if (game->status == WON)
	{
		clear_player(game);
		mlx_put_string(game->mlx, "GOOD JOB! :D", (game->width - 8) * PIXELS / 2, (game->height - 2) * PIXELS / 2);
	}
	mlx_put_string(game->mlx, "(Press ESC to exit...)", (game->width - 13) * PIXELS / 2, game->height* PIXELS / 2);
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(game->mlx);
}

void	fail_game(t_game *game)
{
	clear_player(game);
	game->img_set[PLAYER_FAIL]->enabled = true;
	game->status = FAILED;
	mlx_key_hook(game->mlx, end_game, game);
}

void	check_status(t_game *game)
{
	if (game->collected == game->collectible)
	{
		if (mlx_image_to_window(game->mlx, game->img_set[EXIT_OPEN], game->exit.x * PIXELS, game->exit.y * PIXELS) < 0)
			error_exit("Failed to put image to window");
		game->map[game->exit.y][game->exit.x] = '0';
		if (game->player.x == game->exit.x && game->player.y == game->exit.y)
		{
			game->status = WON;
			mlx_key_hook(game->mlx, end_game, game);
		}
	}
}

void	move(t_game *game, t_drc direction)
{
	char	next_block;

	next_block = get_next_block(game, direction);
	if (next_block != '1' && next_block != 'E')
	{
		clear_player(game);
		move_player(game, direction);
		if (next_block == 'C')
			collect_points(game, game->player.x, game->player.y);
		game->img_set[PLAYER_UP]->instances[0].x = game->player.x * PIXELS;
		game->img_set[PLAYER_UP]->instances[0].y = game->player.y * PIXELS;
		game->img_set[PLAYER_DOWN]->instances[0].x = game->player.x * PIXELS;
		game->img_set[PLAYER_DOWN]->instances[0].y = game->player.y * PIXELS;
		game->img_set[PLAYER_LEFT]->instances[0].x = game->player.x * PIXELS;
		game->img_set[PLAYER_LEFT]->instances[0].y = game->player.y * PIXELS;
		game->img_set[PLAYER_RIGHT]->instances[0].x = game->player.x * PIXELS;
		game->img_set[PLAYER_RIGHT]->instances[0].y = game->player.y * PIXELS;
		game->img_set[PLAYER_FAIL]->instances[0].x = game->player.x * PIXELS;
		game->img_set[PLAYER_FAIL]->instances[0].y = game->player.y * PIXELS;
		// printf("X:player:%d, img:%d\n", game->player.x, game->img_set[PLAYER_UP]->instances[0].x); //
		// printf("Y:player:%d, img:%d\n", game->player.y, game->img_set[PLAYER_UP]->instances[0].y); //
		// printf("moves: %d\n", game->moves);
	}
	mlx_delete_image(game->mlx, game->counts);
	game->counts = mlx_put_string(game->mlx, ft_itoa(game->moves), (game->width + 2) * PIXELS / 2, 0);
	check_status(game);
}

void	move_hook(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *) param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(game->mlx);
	else if ((keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_UP) && keydata.action == MLX_PRESS)
		move(game, UP);
	else if ((keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_DOWN) && keydata.action == MLX_PRESS)
		move(game, DOWN);
	else if ((keydata.key == MLX_KEY_A || keydata.key == MLX_KEY_LEFT) && keydata.action == MLX_PRESS)
		move(game, LEFT);
	else if ((keydata.key == MLX_KEY_D || keydata.key == MLX_KEY_RIGHT) && keydata.action == MLX_PRESS)
		move(game, RIGHT);
}

void	move_all(t_game *game, int i)
{
	t_crd	var;
	int32_t	xi;
	int32_t	yi;

	xi = (rand() % 3 - 1);
	yi = 0;
	if (xi == 0)
		yi = (rand() % 3 - 1);
	var.x = xi + game->img_set[ENEMY]->instances[i].x / PIXELS;
	var.y = yi + game->img_set[ENEMY]->instances[i].y / PIXELS;
	if (game->map[var.y][var.x] != '1' && game->map[var.y][var.x] != 'E')
	{
		game->img_set[ENEMY]->instances[i].x += xi * PIXELS;
		game->img_set[ENEMY]->instances[i].y += yi * PIXELS;
	}
}

void	check_enemy(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->enemy)
	{
		if (game->player.x * PIXELS == game->img_set[ENEMY]->instances[i].x &&
		game->player.y * PIXELS == game->img_set[ENEMY]->instances[i].y)
			fail_game(game);
		i++;
	}
}

void	move_enemy(void *param)
{
	t_game	*game;
	int		i;
	static int	j;

	game = (t_game *) param;
	check_enemy(game);
	if (j++ < 30)
		return ;
	i = 0;
	while (i < game->enemy && game->status == PLAYING)
	{
		move_all(game, i);
		i++;
	}
	j = 0;
}
