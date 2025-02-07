/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 03:09:45 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/07 04:18:21 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int		get_map_width(char **map)
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

int		extend_map(char **map, int width)
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
			temp[j] = map[i][j];
			if (temp[j] == ' ')
				temp[j] = '0';
		}
		while (j < width)
			temp[j++] = '0';
		free(map[i]);
		map[i] = temp;
	}
	return (true);
}

char    **load_map(int fd, char *firstline, int *line_count)
{
	char		*line;
	char		*buffer;
	char		**map;
	
	buffer = ft_strdup(firstline);
	if (!buffer || !str_append(&buffer, "\n"))
		return (NULL);
	while (1)
	{
		line = get_next_line(fd);
		(*line_count)++;
		if (!line || *line == '\n')
		{
			free(line);
			break ;
		}
		if (!str_append(&buffer, line))
			return (free(line), free(buffer), NULL);
		free(line);
	}
	map = ft_split(buffer, '\n');
	return (free(buffer), map);
}