/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 03:09:45 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/14 06:23:31 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	validate_map(char **map)
{
	int		i;
	int		j;
	int		chars[128];

	ft_bzero(chars, 128 * sizeof(int));
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (!ft_strchr(MAP_LAYOUT_CHARS, map[i][j]))
				return (panic("Map Error", ERR_MAP_INVALIDCHAR, false));
			if (map[i][j] == '$' && ((j != 0 && map[i][j - 1] != '1'
				&& map[i][j - 1] != '$') || (j != (int)ft_strlen(map[i]) - 1
				&& map[i][j + 1] != '1' && map[i][j + 1] != '$') || (i != 0
				&& map[i - 1][j] != '1' && map[i - 1][j] != '$') || (map[i + 1]
				&& map[i + 1][j] != '1' && map[i + 1][j] != '$')))
				return (panic("Map Error", ERR_DOUBLE_MAP, false));
			chars[(int)map[i][j]]++;
		}
	}
	if (chars['W'] + chars['S'] + chars['E'] + chars['N'] != 1)
		return (panic("Map Error", ERR_MAP_PLAYER, false));
	return (true);
}

int	is_map_line(char *line)
{
	int		i;

	i = -1;
	while (line[++i])
		if (!ft_strchr(MAP_LAYOUT_CHARS, line[i]))
			return (false);
	return (true);
}

int	get_map_width(char **map)
{
	int		i;
	int		len;
	int		max_width;

	i = -1;
	while (map[++i])
	{
		len = ft_strlen(map[i]);
		if (i == 0 || len > max_width)
			max_width = len;
	}
	return (max_width);
}

int	extend_map(char **map, int width)
{
	int		i;
	int		j;
	char	*temp;

	i = -1;
	while (map[++i])
	{
		temp = ft_calloc(width + 1, sizeof(char));
		if (!temp)
			return (panic("Malloc", NULL, false));
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == ' ')
				temp[j] = '$';
			else
				temp[j] = map[i][j];
		}
		while (j < width)
			temp[j++] = '$';
		free(map[i]);
		map[i] = temp;
	}
	return (true);
}

char	**load_map(int fd, char *firstline, int *line_count)
{
	char		*line;
	char		*buffer;
	char		*trimmed;
	char		**map;

	buffer = ft_strdup(firstline);
	if (!buffer || !str_append(&buffer, "\n"))
		return (NULL);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		(*line_count)++;
		trimmed = ft_strtrim(line, " \n");
		if (!trimmed)
			return (free(line), free(buffer), panic("Trim", NULL, -1), NULL);
		if (!*trimmed)
		{
			free(trimmed);
			free(line);
			break ;
		}
		free(trimmed);
		if (!str_append(&buffer, line))
			return (free(line), free(buffer), NULL);
		free(line);
	}
	map = ft_split(buffer, '\n');
	return (free(buffer), map);
}
