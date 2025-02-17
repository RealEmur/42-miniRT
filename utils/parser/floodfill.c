/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 01:10:20 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/17 03:41:09 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	flood_fill(t_map *map, char **layout, int x, int y)
{
	if (y < 0 || x < 0 || y >= map->height || x >= (int)ft_strlen(layout[y]))
		return ;
	if (layout[y][x] == FILL_CHAR)
		return ;
	layout[y][x] = FILL_CHAR;
	flood_fill(map, layout, y + 1, x);
	flood_fill(map, layout, y - 1, x);
	flood_fill(map, layout, y, x + 1);
	flood_fill(map, layout, y, x - 1);
}

int	check_walls(t_map *map, t_player *player)
{
	int				i;
	int				j;
	char **const	copied_map = ft_strarrdup(map->layout);

	flood_fill(map, copied_map, \
	(int)player->position.x, (int)player->position.y);
	i = -1;
	while (++i < map->height)
	{
		j = -1;
		while (++j < (int)ft_strlen(copied_map[i]))
			if (copied_map[i][j] == '0' || copied_map[i][j] == '1')
				return (1);
	}
	return (0);
}
