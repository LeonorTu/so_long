/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 19:25:04 by jtu               #+#    #+#             */
/*   Updated: 2024/02/22 15:29:59 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	get_next_block(t_game *game, t_drc direction)
{
	t_crd	next;

	next = (t_crd){game->player_crd.x, game->player_crd.y};
	if (direction == UP)
		next.y--;
	else if (direction == DOWN)
		next.y++;
	else if (direction == LEFT)
		next.x--;
	else if (direction == RIGHT)
		next.x++;
	return (game->map[next.y][next.x]);
}

void	clear_player(t_game *game)
{
	game->img_set[PLAYER_STAND]->enabled = false;
	game->img_set[PLAYER_UP]->enabled = false;
	game->img_set[PLAYER_DOWN]->enabled = false;
	game->img_set[PLAYER_LEFT]->enabled = false;
	game->img_set[PLAYER_RIGHT]->enabled = false;
	game->img_set[PLAYER_FAIL]->enabled = false;
}

void	collect_points(t_game *game, int32_t x, int32_t y)
{
	int	i;

	i = 0;
	while (i < game->collectible)
	{
		if (game->img_set[COLLECTIBLE]->instances[i].x == x * PIXELS && \
		game->img_set[COLLECTIBLE]->instances[i].y == y * PIXELS)
			game->img_set[COLLECTIBLE]->instances[i].enabled = false;
		i++;
	}
	game->map[y][x] = '0';
	game->collected++;
}

void	check_status(t_game *game)
{
	if (game->collected == game->collectible)
	{
		if (mlx_image_to_window(game->mlx, game->img_set[EXIT_OPEN], \
		game->exit_crd.x * PIXELS, game->exit_crd.y * PIXELS) < 0)
			error_exit("Failed to put image to window");
		game->map[game->exit_crd.y][game->exit_crd.x] = '0';
		game->exit = 0;
		if (game->player_crd.x == game->exit_crd.x && game->player_crd.y \
		== game->exit_crd.y)
		{
			game->status = WON;
			clear_player(game);
			mlx_put_string(game->mlx, "GOOD JOB! :D", (game->width - 8) * \
			PIXELS / 2, (game->height - 2) * PIXELS / 2);
			mlx_key_hook(game->mlx, end_game, game);
		}
	}
}
