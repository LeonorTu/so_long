/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 13:20:52 by jtu               #+#    #+#             */
/*   Updated: 2024/02/20 18:20:06 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_rectangle(char **map)
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

void	check_char(int c)
{
	if (!ft_strchr("01CEPX\n", c))
		error_exit("Invalid Characters\n");
}

void	check_wall(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
		i++;
	while (map[0][j] && map[i - 1][j])
	{
		if (map[0][j]  != '1' || map[i - 1][j] != '1')
			error_exit("Invalid Walls\n");
		j++;
	}
	i = 1;
	j = ft_strlen(map[i]);
	while (map[i])
	{
		if (map[i][0]  != '1' || map[i][j-1] != '1')
			error_exit("Invalid Walls\n");
		i++;
	}
}

void	check_pec(t_game *game)
{
	int	exit;
	int	player;
	int	i;
	int	j;

	exit = 0;
	player = 0;
	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'C')
				game->collectible++;
			else if (game->map[i][j] == 'X')
				game->enemy++;
			else if (game->map[i][j] == 'E')
			{
				exit++;
				game->exit.y = i;
				game->exit.x = j;
			}
			else if (game->map[i][j] == 'P')
			{
				player++;
				game->player.y = i;
				game->player.x = j;
			}
			else
				check_char(game->map[i][j]);
			j++;
		}
		i++;
	}
	if (game->collectible < 1 || exit != 1 || player != 1)
		error_exit("Invalid Map Content\n");
}

int	check_valid(t_game *game, char **map, int32_t x, int32_t y)
{
	static int	collected;
	static int	exit;

	if (map[y][x] == 'E')
		exit = 1;
	if (map[y][x] == 'C')
		collected++;
	map[y][x] = '1';
	// if (x < game->width - 1 && y < game->height -1)
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
	i = 0;
	while(i < game->height)
	{
		temp[i] = ft_strdup(game->map[i]);
		i++;
	}
	if (!check_valid(game, temp, game->player.x, game->player.y))
		error_exit("Invalid Map Path\n");
}
