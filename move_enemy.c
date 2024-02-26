/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:17:11 by jtu               #+#    #+#             */
/*   Updated: 2024/02/26 14:17:29 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	move_all(t_game *game, int i)
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
		if (game->player_crd.x * PIXELS == game->img_set[ENEMY]->instances[i].x \
		&& game->player_crd.y * PIXELS == game->img_set[ENEMY]->instances[i].y)
		{
			clear_player(game);
			game->img_set[PLAYER_FAIL]->enabled = true;
			game->status = FAILED;
			mlx_put_string(game->mlx, "YOU LOST :(", (game->width - 7) * \
			PIXELS / 2, (game->height - 2) * PIXELS / 2);
			mlx_key_hook(game->mlx, end_game, game);
		}
		i++;
	}
}

void	move_enemy(void *param)
{
	t_game		*game;
	int			i;
	static int	j;

	game = (t_game *) param;
	check_enemy(game);
	if (j++ < TIME_ENEMY)
		return ;
	i = 0;
	while (i < game->enemy && game->status == PLAYING)
	{
		move_all(game, i);
		i++;
	}
	j = 0;
}
