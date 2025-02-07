/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:17:58 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/07 14:32:52 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int	validate_props(char **props, char *types, int line)
{
	int		i;
	char	identifier;
	const	int size = ft_strlen(types);

	if (str_arr_size(props) != size + 1)
		return (parser_panic(ERROR, line, props[0], ERR_WRONG_FORMAT), false);
	i = 0;
	while (++i < size + 1)
	{
		identifier = types[i - 1];
		if (identifier == 'X' && !validate_extension(props[i], ".xpm"))
			return (parser_panic(ERROR, line, props[i], ERR_ARG_XPM), false);
		if (identifier == 'R' && !is_rgb(props[i]))
			return (parser_panic(ERROR, line, props[i], ERR_ARG_RGB), false);
		if (identifier == 'R' && !validate_rgb(strtorgb(props[i])))
			return (parser_panic(ERROR, line, props[i], ERR_RGB_RANGE), false);
	}
	return (1);
}

int	parse_texture(t_scene *scene, char **props, int type, int line)
{
	char	**const texture = &scene->options.textures[type - 2];
	
	if (!validate_props(props, "X", line))
		return (false);
	if (*texture)
	{
		parser_panic(WARNING, line, "Multiple Texture", ERR_MULTIPLE_TEXTURE);
		free(*texture);
	}
	*texture = ft_strdup(props[1]);
	if (!*texture)
		return (panic("String Duplication", NULL, false));
	return (true);
}

int	parse_color(t_scene *scene, char **props, int type, int line)
{
	t_rgb	**const color = &scene->options.colors[type - 6]; 
	
	if (!validate_props(props, "R", line))
		return (false);
	if (!*color)
	{
		*color = ft_calloc(1, sizeof(t_rgb));
		if (!*color)
			return (panic("Malloc Error", NULL, false));
	}
	else 
		parser_panic(WARNING, line, "Multiple Color", ERR_MULTIPLE_COLOR);
	**color = strtorgb(props[1]);
	return (true);
}

int parse_map(t_scene *scene, int fd, char *line, int *line_count)
{
	t_map	*const map = &scene->map;
	char	**const map_layout = load_map(fd, line, line_count);

	if (!map_layout)
		return (panic("Reading Map", NULL, 0));
	map->height = str_arr_size(map_layout);
	map->width = get_map_width(map_layout);
	extend_map(map_layout, map->width);
	map->layout = map_layout;
	line = get_next_line(fd);
	if (line)
		return (free(line), parser_panic(ERROR, ++(*line_count), "Map File", ERR_MAP_NOTLAST), false);
	return (true);
}	
