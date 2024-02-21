/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:20:52 by jtu               #+#    #+#             */
/*   Updated: 2024/02/21 14:18:36 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static void	check_rectangle(char **map)
{
	int		i;

	i = 1;
	while (map[i])
	{
		if (ft_strlen(map[i]) != ft_strlen(map[0]))
			error_exit("Non-rectangular Map\n");
		i++;
	}
}

static void	check_wall(char **map)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (map[y])
		y++;
	while (map[0][x] && map[y - 1][x])
	{
		if (map[0][x] != '1' || map[y - 1][x] != '1')
			error_exit("Invalid Walls\n");
		x++;
	}
	y = 1;
	x = ft_strlen(map[y]);
	while (map[y])
	{
		if (map[y][0] != '1' || map[y][x - 1] != '1')
			error_exit("Invalid Walls\n");
		y++;
	}
}

static void	check_pec(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] == 'C')
				game->collectible++;
			else if (game->map[y][x] == 'X')
				game->enemy++;
			else if (game->map[y][x] == 'E')
				game->exit++;
			else if (game->map[y][x] == 'P')
				game->player++;
			else
				check_char(game->map[y][x]);
			x++;
		}
		y++;
	}
	if (game->collectible < 1 || game->exit != 1 || game->player != 1)
		error_exit("Invalid Map Content\n");
}

static int	check_valid(t_game *game, char **map, int32_t x, int32_t y)
{
	static int	collected;
	static int	exit;

	if (map[y][x] == 'E')
		exit++;
	if (map[y][x] == 'C')
		collected++;
	map[y][x] = '1';
	if (map[y + 1][x] != '1')
		check_valid(game, map, x, y + 1);
	if (map[y - 1][x] != '1')
		check_valid(game, map, x, y - 1);
	if (map[y][x + 1] != '1')
		check_valid(game, map, x + 1, y);
	if (map[y][x - 1] != '1')
		check_valid(game, map, x - 1, y);
	if (exit == 1 && collected == game->collectible)
		return (1);
	return (0);
}

void	check_map(t_game *game)
{
	char	**temp;
	int		i;

	check_rectangle(game->map);
	check_wall(game->map);
	check_pec(game);
	temp = malloc(game->height * sizeof(char *));
	if (!temp)
		error_exit("Memory Allocation Failed\n");
	i = 0;
	while (i < game->height)
	{
		temp[i] = ft_strdup(game->map[i]);
		i++;
	}
	get_crd(game);
	if (!check_valid(game, temp, game->player_crd.x, game->player_crd.y))
		error_exit("Invalid Map Path\n");
	delete_map(temp, game->height);
}
