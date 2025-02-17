/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 03:09:45 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/17 18:55:03 by tkul             ###   ########.fr       */
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
		temp = ft_calloc(width + 2, sizeof(char));
		if (!temp)
			return (panic("Malloc", NULL, false));
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] == ' ')
				temp[j] = FILL_CHAR;
			else
				temp[j] = map[i][j];
		}
		while (j < width)
			temp[j++] = FILL_CHAR;
		temp[j++] = FILL_CHAR;
		free(map[i]);
		map[i] = temp;
	}
	return (true);
}

char	**load_map(int fd, char *firstline, int *line_count)
{
	void		*temp;
	char		*buffer;
	char		*trimmed;

	buffer = ft_strdup(firstline);
	if (!buffer || !str_append(&buffer, "\n"))
		return (NULL);
	while (fd != -1)
	{
		temp = get_next_line(fd);
		if (!temp)
			break ;
		(*line_count)++;
		trimmed = ft_strtrim(temp, " \n");
		if (!trimmed)
			return (free(temp), free(buffer), panic("Trim", NULL, -1), NULL);
		if (!*trimmed)
			fd = -1;
		free(trimmed);
		if (!str_append(&buffer, temp))
			return (free(temp), free(buffer), panic("Append", NULL, -1), NULL);
		free(temp);
	}
	temp = ft_split(buffer, '\n');
	return (free(buffer), temp);
}
