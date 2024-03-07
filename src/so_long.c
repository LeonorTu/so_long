/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:42:53 by jtu               #+#    #+#             */
/*   Updated: 2024/03/07 20:24:21 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/so_long.h"

static void	init_game(t_game *game)
{
	game->width = 0;
	game->height = 0;
	game->moves = 0;
	game->player = 0;
	game->exit = 0;
	game->collectible = 0;
	game->enemy = 0;
	game->collected = 0;
	game->status = PLAYING;
}

int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc != 2)
		error_exit("Invalid Input\n");
	init_game(&game);
	check_file(argv[1]);
	read_map(&game, argv[1]);
	check_map(&game);
	init_img(&game);
	display_img(&game);
	mlx_key_hook(game.mlx, move_hook, &game);
	mlx_loop_hook(game.mlx, move_enemy, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	delete_map(game.map, game.height);
	return (EXIT_SUCCESS);
}
