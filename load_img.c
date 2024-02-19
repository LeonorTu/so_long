/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:13:42 by jtu               #+#    #+#             */
/*   Updated: 2024/02/19 16:39:29 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	load_img(mlx_t *mlx, mlx_image_t **img, char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
		error_exit("Loading image failed!\n");
	*img = mlx_texture_to_image(mlx, texture);
	if (!*img)
		error_exit("Texture to image failed!\n");
	mlx_delete_texture(texture);
}

void	init_img(t_game *game)
{
	load_img(game->mlx, &game->img_set[START], "assets/start.png");
	load_img(game->mlx, &game->img_set[EXIT_CLOSED], "assets/exit_closed.png");
	load_img(game->mlx, &game->img_set[EXIT_OPEN], "assets/exit_open.png");
	load_img(game->mlx, &game->img_set[GRASS], "assets/grass.png");
	load_img(game->mlx, &game->img_set[WALL], "assets/water.png");
	load_img(game->mlx, &game->img_set[PLAYER_STAND], "assets/stand.png");
	load_img(game->mlx, &game->img_set[PLAYER_UP], "assets/up.png");
	load_img(game->mlx, &game->img_set[PLAYER_DOWN], "assets/down.png");
	load_img(game->mlx, &game->img_set[PLAYER_LEFT], "assets/left.png");
	load_img(game->mlx, &game->img_set[PLAYER_RIGHT], "assets/right.png");
	load_img(game->mlx, &game->img_set[PLAYER_FAIL], "assets/fail.png");
	load_img(game->mlx, &game->img_set[COLLECTIBLE], "assets/egg.png");
	load_img(game->mlx, &game->img_set[ENEMY], "assets/chicken.png");
}

// void	select_img(t_game *game, int x, int y)
// {
// 	if (game->map[y][x] == 'P')
// 	{
// 		if (mlx_image_to_window(game->mlx, game->img_set[PLAYER_STAND], x * PIXELS, y * PIXELS) < 0)
// 				error_exit("Failed to put image to window");
// 		if (mlx_image_to_window(game->mlx, game->img_set[PLAYER_UP], x * PIXELS, y * PIXELS) < 0)
// 				error_exit("Failed to put image to window");
// 		if (mlx_image_to_window(game->mlx, game->img_set[PLAYER_DOWN], x * PIXELS, y * PIXELS) < 0)
// 				error_exit("Failed to put image to window");
// 		if (mlx_image_to_window(game->mlx, game->img_set[PLAYER_LEFT], x * PIXELS, y * PIXELS) < 0)
// 				error_exit("Failed to put image to window");
// 		if (mlx_image_to_window(game->mlx, game->img_set[PLAYER_RIGHT], x * PIXELS, y * PIXELS) < 0)
// 				error_exit("Failed to put image to window");
// 		if (mlx_image_to_window(game->mlx, game->img_set[PLAYER_FAIL], x * PIXELS, y * PIXELS) < 0)
// 				error_exit("Failed to put image to window");
// 		clear_player(game);
// 		game->img_set[PLAYER_STAND]->enabled = true;
// 	}
// }

void	display_bg(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (mlx_image_to_window(game->mlx, game->img_set[GRASS], x * PIXELS, y * PIXELS) < 0)
				error_exit("Failed to put image to window");
			if (game->map[y][x] == '1')
				if (mlx_image_to_window(game->mlx, game->img_set[WALL], x * PIXELS, y * PIXELS) < 0)
						error_exit("Failed to put image to window");
			if (game->map[y][x] == 'C')
				if (mlx_image_to_window(game->mlx, game->img_set[COLLECTIBLE], x * PIXELS, y * PIXELS) < 0)
						error_exit("Failed to put image to window");
			if (game->map[y][x] == 'E')
				if (mlx_image_to_window(game->mlx, game->img_set[EXIT_CLOSED], x * PIXELS, y * PIXELS) < 0)
						error_exit("Failed to put image to window");
			x++;
		}
		y++;
	}
}

void	display_player(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < game->height)
	{
		x = 0;
		while (x < game->width)
		{
			if (game->map[y][x] == 'P')
			{
				if (mlx_image_to_window(game->mlx, game->img_set[PLAYER_STAND], x * PIXELS, y * PIXELS) < 0)
						error_exit("Failed to put image to window");
				if (mlx_image_to_window(game->mlx, game->img_set[PLAYER_UP], x * PIXELS, y * PIXELS) < 0)
						error_exit("Failed to put image to window");
				if (mlx_image_to_window(game->mlx, game->img_set[PLAYER_DOWN], x * PIXELS, y * PIXELS) < 0)
						error_exit("Failed to put image to window");
				if (mlx_image_to_window(game->mlx, game->img_set[PLAYER_LEFT], x * PIXELS, y * PIXELS) < 0)
						error_exit("Failed to put image to window");
				if (mlx_image_to_window(game->mlx, game->img_set[PLAYER_RIGHT], x * PIXELS, y * PIXELS) < 0)
						error_exit("Failed to put image to window");
				if (mlx_image_to_window(game->mlx, game->img_set[PLAYER_FAIL], x * PIXELS, y * PIXELS) < 0)
						error_exit("Failed to put image to window");
				clear_player(game);
				game->img_set[PLAYER_STAND]->enabled = true;
			}
			if (game->map[y][x] == 'X')
				if (mlx_image_to_window(game->mlx, game->img_set[ENEMY], x * PIXELS, y * PIXELS) < 0)
						error_exit("Failed to put image to window");
			x++;
		}
		y++;
	}
}

void	display_img(t_game *game)
{
	display_bg(game);
	display_player(game);
	mlx_put_string(game->mlx, "Moves:", (game->width - 6) * PIXELS / 2, 0);
	game->counts = mlx_put_string(game->mlx, "0", (game->width + 2) * PIXELS / 2, 0);
}