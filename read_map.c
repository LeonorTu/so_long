/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtu <jtu@student.hive.fi>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:58:54 by jtu               #+#    #+#             */
/*   Updated: 2024/02/26 13:43:00 by jtu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	read_map(t_game *game, char *file)
{
	int		fd;
	char	*line;
	char	*holder;
	char	*all_lines;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_exit("Unreadable Map");
	line = get_next_line(fd);
	if (line)
		game->width = ft_strlen(line) - 1;
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
	game->map_s = all_lines;
	game->map = ft_split(all_lines, '\n');
	free(line);
	close(fd);
}
