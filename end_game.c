/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_game.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:14:19 by jtu               #+#    #+#             */
/*   Updated: 2024/02/22 15:22:19 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	end_game(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = (t_game *) param;
	mlx_put_string(game->mlx, "(Press ESC to exit...)", (game->width - 13) \
	* PIXELS / 2, game->height * PIXELS / 2);
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(game->mlx);
}
