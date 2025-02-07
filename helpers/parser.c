/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:59:26 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/07 04:29:15 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	is_map_line(char *line)
{
	int		i;

	i = -1;
	while (line[++i])
		if (!ft_strchr(MAP_MAPLAYOUT_CHARS, line[i]))
			return (false);
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

int	parse_elements(int fd, t_scene *scene)
{
	int			line_count;
	int			type;
	char		*line;
	char		*trimmed;
	char		**splitted;
	
	line_count = 1;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		trimmed = ft_strtrim(line, "\n");
		if (!trimmed)
			return (free(line), panic("Trim Failed", NULL, false));
		splitted = ft_split(trimmed, ' ');
		if (!splitted)
			return (free(line), free(trimmed), panic("Split Failed", NULL, false));
		type = get_line_type(trimmed, splitted);
		if (type == MAPKEY_INVALID)
			return (free(line), free(trimmed), free_str_arr(splitted), parser_panic(line_count, "Unrecognized Identifier", ERR_INVALID_INDETIFIER), false);
		else if (type != MAPKEY_NOTHING 
			&& ((type < MAP_LAYOUT && !parse_element(scene, splitted, type, line_count))
			|| (type == MAP_LAYOUT && !parse_map(scene, fd, trimmed, &line_count))))
			return (free(line), free(trimmed), false);
		line_count++;
		free_str_arr(splitted);
		free(trimmed);
		free(line);
	}
	return (true);
}

int	parser(char *path, t_scene *scene)
{
	int		fd;
	
	(void)scene;
	if (!validate_extension(path, MAP_FILE_EXTENSION))
		return (panic(path, ERR_EXTENSION, false), false);
    fd = open(path, O_RDONLY);
    if (fd == -1)
		return (panic(path, NULL, false), false);
	if (!parse_elements(fd, scene))
		return (false);
    return (true);   
}