/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:42:53 by jtu               #+#    #+#             */
/*   Updated: 2024/02/20 16:53:44 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_file(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(file + len - 4, ".ber", 4))
		error_exit("Invalid Map\n");
}

void	read_map(t_game *game, char *file)
{
	int		fd;
	char	*line;
	char	*holder;
	char	*all_lines;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return ;
	line = get_next_line(fd);
	game->width = ft_strlen(line);
	all_lines = ft_strdup("");
	while (line)
	{
		game->height++;
		holder = all_lines;
		all_lines = ft_strjoin(holder, line);
		free(line);
		free(holder);
		line = get_next_line(fd);
	}
	game->map = ft_split(all_lines, '\n');
	free(line);
	free(all_lines);
	close(fd);
}

void	init_game(t_game *game)
{
	game->width = 0;
	game->height = 0;
	game->moves = 0;
	game->collectible = 0;
	game->enemy = 0;
	game->collected = 0;
	game->status = PLAYING;
}

static void	delete_map(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
		free(map[i++]);
	free(map);
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
	delete_map(game.map);
	return (EXIT_SUCCESS);
}
