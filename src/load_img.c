/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:13:42 by jtu               #+#    #+#             */
/*   Updated: 2024/03/07 20:24:21 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static void	load_img(mlx_t *mlx, mlx_image_t **img, char *path)
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
	game->mlx = mlx_init(game->width * PIXELS, game->height * \
	PIXELS, "so_long", false);
	if (!game->mlx)
		error_exit("mlx_init failed");
	load_img(game->mlx, &game->img_set[GRASS], "textures/grass.png");
	load_img(game->mlx, &game->img_set[WALL], "textures/water.png");
	load_img(game->mlx, &game->img_set[START], "textures/start.png");
	load_img(game->mlx, &game->img_set[EXIT_CLOSED], \
	"textures/exit_closed.png");
	load_img(game->mlx, &game->img_set[EXIT_OPEN], "textures/exit_open.png");
	load_img(game->mlx, &game->img_set[COLLECTIBLE], "textures/egg.png");
	load_img(game->mlx, &game->img_set[PLAYER_STAND], "textures/stand.png");
	load_img(game->mlx, &game->img_set[PLAYER_UP], "textures/up.png");
	load_img(game->mlx, &game->img_set[PLAYER_DOWN], "textures/down.png");
	load_img(game->mlx, &game->img_set[PLAYER_LEFT], "textures/left.png");
	load_img(game->mlx, &game->img_set[PLAYER_RIGHT], "textures/right.png");
	load_img(game->mlx, &game->img_set[PLAYER_FAIL], "textures/fail.png");
	load_img(game->mlx, &game->img_set[ENEMY], "textures/chicken.png");
}
