/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 12:48:32 by jtu               #+#    #+#             */
/*   Updated: 2024/02/21 12:50:11 by jtu              ###   ########.fr       */
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

void	check_char(int c)
{
	if (!ft_strchr("01CEPX\n", c))
		error_exit("Invalid Characters\n");
}

void	get_crd(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map[i])
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == 'E')
				game->exit_crd = (t_crd){j, i};
			else if (game->map[i][j] == 'P')
				game->player_crd = (t_crd){j, i};
			j++;
		}
		i++;
	}
}
