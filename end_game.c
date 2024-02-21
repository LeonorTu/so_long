/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:14:19 by jtu               #+#    #+#             */
/*   Updated: 2024/02/21 12:33:37 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	end_game(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *) param;
	if (game->status == FAILED)
		mlx_put_string(game->mlx, "YOU LOST :(", (game->width - 7) * \
		PIXELS / 2, (game->height - 2) * PIXELS / 2);
	else if (game->status == WON)
	{
		clear_player(game);
		mlx_put_string(game->mlx, "GOOD JOB! :D", (game->width - 8) * \
		PIXELS / 2, (game->height - 2) * PIXELS / 2);
	}
	mlx_put_string(game->mlx, "(Press ESC to exit...)", (game->width - 13) \
	* PIXELS / 2, game->height * PIXELS / 2);
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(game->mlx);
}
