/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 15:42:53 by jtu               #+#    #+#             */
/*   Updated: 2024/02/19 14:06:22 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_map(char **map) //
{
	int i = 0;
	while (map[i])
	{
		ft_putstr_fd(map[i], 1); // Print each row of the map
		ft_putchar_fd('\n', 1);   // Move to the next line
		i++;
	}
}

void	check_file(char *file)
{
	size_t	len;

	len = ft_strlen(file);
	if (len < 4 || ft_strncmp(file + len - 4, ".ber", 4))
		error_exit("Invalid Map\n");
}

char	**read_map(char *file)
{
	int		fd;
	char	*line;
	char	*all_lines;
	char	**map;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	all_lines = ft_strdup("");
	while (line)
	{
		all_lines = ft_strjoin(all_lines, line);
		free(line);
		line = get_next_line(fd);
	}
	map = ft_split(all_lines, '\n');
	free(all_lines);
	close(fd);
	return (map);
}

void	init_game(t_game *game)
{
	int32_t	i;

	i = 0;
	while (game->map[i])
		i++;
	game->width = (int32_t)ft_strlen(game->map[0]);
	game->height = i;
	game->moves = 0;
	game->collectible = 0;
	game->enemy = 0;
	game->collected = 0;
	game->status = PLAYING;
	game->mlx = mlx_init(game->width * PIXELS, game->height * PIXELS, "so_long", true);
	if (!game->mlx)
		error_exit("mlx_init failed");
}

// static void	delete_map(char **map)
// {
// 	int	i;

// 	i = 0;
// 	while (map[i] != NULL)
// 		free(map[i++]);
// 	free(map);
// }


int	main(int argc, char *argv[])
{
	t_game	game;

	if (argc != 2)
		error_exit("Invalid Input\n");
	check_file(argv[1]);
	game.map = read_map(argv[1]);
	init_game(&game);
	check_map(&game);
	// print_map(game.map);
	init_img(&game);
	game.map = read_map(argv[1]); // need editing
	display_img(&game);
	mlx_key_hook(game.mlx, move_hook, &game);
	mlx_loop_hook(game.mlx, move_enemy, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	// delete_map(game.map);
	return (EXIT_SUCCESS);
}
