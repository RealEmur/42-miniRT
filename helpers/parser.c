/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:59:26 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/17 04:53:15 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_inputs(t_scene *scene)
{
	int		i;

	if (!scene->map.layout)
		return (panic("Map Required", ERR_MAP_REQUIRED, false));
	i = -1;
	while (++i < TEXTURE_COUNT)
		if (!scene->options.textures[i].path)
			return (panic("Textures", ERR_TEXTURE_MISSING, false));
	i = -1;
	while (++i < COLOR_COUNT)
		if (!scene->options.colors[i])
			return (panic("Colors", ERR_COLOR_MISSING, false));
	return (true);
}

int	get_line_type(char *line, char **props)
{
	char	*identifier;

	if (!*line)
		return (MAPKEY_NOTHING);
	else if (str_arr_size(props) > 0)
	{
		identifier = props[0];
		if (!ft_strncmp(identifier, "NO", 3))
			return (TEXTURE_NORTH);
		else if (!ft_strncmp(identifier, "SO", 3))
			return (TEXTURE_SOUTH);
		else if (!ft_strncmp(identifier, "WE", 3))
			return (TEXTURE_WEST);
		else if (!ft_strncmp(identifier, "EA", 3))
			return (TEXTURE_EAST);
		else if (!ft_strncmp(identifier, "F", 2))
			return (COLOR_FLOOR);
		else if (!ft_strncmp(identifier, "C", 2))
			return (COLOR_CEILING);
	}
	if (is_map_line(line))
		return (MAP_LAYOUT);
	return (MAPKEY_INVALID);
}

int	parse_element(t_scene *scene, char **props, int type, int line_count)
{
	if (type == TEXTURE_EAST
		|| type == TEXTURE_NORTH
		|| type == TEXTURE_SOUTH
		|| type == TEXTURE_WEST)
		return (parse_texture(scene, props, type, line_count));
	else if (type == COLOR_CEILING || type == COLOR_FLOOR)
		return (parse_color(scene, props, type, line_count));
	return (false);
}

int	parse_line(t_scene *scene, char *line, int line_count, int fd)
{
	int			type;
	char		*trimmed;
	char		**splitted;

	trimmed = ft_strtrim(line, "\n");
	if (!trimmed)
		return (free(line), panic("Trim Failed", NULL, false));
	splitted = ft_split(trimmed, ' ');
	if (!splitted)
		return (free(line), free(trimmed), panic("Split", NULL, false));
	type = get_line_type(trimmed, splitted);
	if (type == MAPKEY_INVALID)
		return (free(line), free(trimmed), free_str_arr(splitted), \
		parser_panic(line_count, "Identifier", ERR_INVALID_IDENTIFIER), false);
	else if (type != MAPKEY_NOTHING
		&& ((type < MAP_LAYOUT
				&& !parse_element(scene, splitted, type, line_count))
			|| (type == MAP_LAYOUT
				&& !parse_map(scene, fd, trimmed, &line_count))))
		return (free(line), free(trimmed), free_str_arr(splitted), false);
	line_count++;
	free_str_arr(splitted);
	free(trimmed);
	return (true);
}

int	parser(char *path, t_scene *scene)
{
	int		fd;
	int		line_count;
	char	*line;

	if (!validate_extension(path, MAP_FILE_EXTENSION))
		return (panic(path, ERR_EXTENSION, false), false);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (panic(path, NULL, false), false);
	line_count = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (!parse_line(scene, line, line_count++, fd))
			return (close(fd), free(line), false);
		free(line);
	}
	if (!check_inputs(scene))
		return (close(fd), false);
	close(fd);
	return (true);
}
