/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_img.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:06:45 by jtu               #+#    #+#             */
/*   Updated: 2024/02/21 13:22:06 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	select_img(t_game *game, int32_t x, int32_t y)
{
	if (game->map[y][x] == '1')
		if (mlx_image_to_window(game->mlx, game->img_set[WALL], \
		x * PIXELS, y * PIXELS) < 0)
			error_exit("Failed to put image to window");
	if (game->map[y][x] == 'C')
		if (mlx_image_to_window(game->mlx, game->img_set[COLLECTIBLE], \
		x * PIXELS, y * PIXELS) < 0)
			error_exit("Failed to put image to window");
	if (game->map[y][x] == 'E')
		if (mlx_image_to_window(game->mlx, game->img_set[EXIT_CLOSED], \
		x * PIXELS, y * PIXELS) < 0)
			error_exit("Failed to put image to window");
}

static void	display_bg(t_game *game)
{
	int32_t	x;
	int32_t	y;

	x = 0;
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (mlx_image_to_window(game->mlx, game->img_set[GRASS], \
			x * PIXELS, y * PIXELS) < 0)
				error_exit("Failed to put image to window");
			select_img(game, x, y);
			x++;
		}
		y++;
	}
}

static void	display_player(t_game *game, int32_t x, int32_t y)
{
	if (mlx_image_to_window(game->mlx, game->img_set[PLAYER_STAND], \
	x * PIXELS, y * PIXELS) < 0)
		error_exit("Failed to put image to window");
	if (mlx_image_to_window(game->mlx, game->img_set[PLAYER_UP], \
	x * PIXELS, y * PIXELS) < 0)
		error_exit("Failed to put image to window");
	if (mlx_image_to_window(game->mlx, game->img_set[PLAYER_DOWN], \
	x * PIXELS, y * PIXELS) < 0)
		error_exit("Failed to put image to window");
	if (mlx_image_to_window(game->mlx, game->img_set[PLAYER_LEFT], \
	x * PIXELS, y * PIXELS) < 0)
		error_exit("Failed to put image to window");
	if (mlx_image_to_window(game->mlx, game->img_set[PLAYER_RIGHT], \
	x * PIXELS, y * PIXELS) < 0)
		error_exit("Failed to put image to window");
	if (mlx_image_to_window(game->mlx, game->img_set[PLAYER_FAIL], \
	x * PIXELS, y * PIXELS) < 0)
		error_exit("Failed to put image to window");
}

static void	display_pe(t_game *game)
{
	int32_t	x;
	int32_t	y;

	x = 0;
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == 'P')
			{
				display_player(game, x, y);
				clear_player(game);
				game->img_set[PLAYER_STAND]->enabled = true;
			}
			if (game->map[y][x] == 'X')
				if (mlx_image_to_window(game->mlx, game->img_set[ENEMY], x \
				* PIXELS, y * PIXELS) < 0)
					error_exit("Failed to put image to window");
			x++;
		}
		y++;
	}
}

void	display_img(t_game *game)
{
	display_bg(game);
	display_pe(game);
	mlx_put_string(game->mlx, "Moves:", (game->width - 6) * PIXELS / 2, 0);
	game->counts = mlx_put_string(game->mlx, "0", (game->width + 2) \
	* PIXELS / 2, 0);
}
