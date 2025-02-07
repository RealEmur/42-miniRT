/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:17:58 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/07 04:30:20 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int	validate_props(char **props, char *types, int line)
{
	int		i;
	char	identifier;
	const	int size = ft_strlen(types);

	if (str_arr_size(props) != size + 1)
		return (parser_panic(line, props[0], ERR_WRONG_FORMAT), false);
	i = 0;
	while (++i < size + 1)
	{
		identifier = types[i - 1];
		if (identifier == 'X' && !validate_extension(props[i], ".xpm"))
			return (parser_panic(line, props[i], ERR_ARG_XPM), false);
		if (identifier == 'R' && !is_rgb(props[i]))
			return (parser_panic(line, props[i], ERR_ARG_RGB), false);
		if (identifier == 'R' && !validate_rgb(strtorgb(props[i])))
			return (parser_panic(line, props[i], ERR_RGB_RANGE), false);
	}
	return (1);
}

int	parse_texture(t_scene *scene, char **props, int type, int line)
{
	char	**const texture = &scene->options.textures[type];
	
	if (!validate_props(props, "X", line))
		return (false);
	*texture = ft_strdup(props[1]);
	if (!*texture)
		return (panic("String Duplication", NULL, false));
	return (true);
}

int	parse_color(t_scene *scene, char **props, int type, int line)
{
	t_rgb	*color = &scene->options.colors[type];
	
	if (!validate_props(props, "R", line))
		return (false);
	*color = strtorgb(props[1]);
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
	for (int i = 0; map_layout[i]; i++)
	{
		printf("%s\n", map_layout[i]);
	}
	line = get_next_line(fd);
	if (line)
		return (free(line), parser_panic(++(*line_count), "Map File", ERR_MAP_NOTLAST), false);
	return (true);
}	

/* t_object	*parse_ambient(char **props, int line)
{
	t_ambient	*ambient; 
	
	if (!validate_props(props, "FR", line))
		return (NULL);
	ambient = ft_calloc(1, sizeof(t_ambient));
	if (!ambient)
		return (panic(NULL, NULL, -1), NULL);
	ambient->type = AMBIENT_LIGHTNING;
	ambient->brightness = strtofloat(props[1]);
	ambient->color = strtorgb(props[2]);
	return ((t_object *)ambient);
}

t_object	*parse_camera(char **props, int line)
{
	t_camera	*camera;
	
	if (!validate_props(props, "PVN", line))
		return (NULL);
	camera = ft_calloc(1, sizeof(t_camera));
	if (!camera)
		return (panic(NULL, NULL, -1), NULL);
	camera->type = CAMERA;
	camera->position = strtocoord(props[1]);
	camera->vector	= strtocoord(props[2]);
	camera->fov	= ft_atoi(props[3]);
	return ((t_object *)camera);
}

t_object	*parse_light(char **props, int line)
{
	t_light	*light;

	if (!validate_props(props, "PFR", line))
		return (NULL);
	light = ft_calloc(1, sizeof(t_light));
	if (!light)
		return (panic(NULL, NULL, -1), NULL);
	light->type = LIGHT;
	light->position = strtocoord(props[1]);
	light->brightness = strtofloat(props[2]);
	light->color = strtorgb(props[3]);
	return ((t_object *)light);
}

t_object	*parse_sphere(char **props, int line)
{
	t_sphere	*sphere;
	
	if (!validate_props(props, "PFR", line))
		return (NULL);
	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (panic(NULL, NULL, -1), NULL);
	sphere->type = SPHERE;
	sphere->position = strtocoord(props[1]);
	sphere->diameter = strtofloat(props[2]);
	sphere->color = strtorgb(props[3]);
	return ((t_object *)sphere);
}

t_object	*parse_plane(char **props, int line)
{
	t_plane	*plane;
	
	if (!validate_props(props, "PVR", line))
		return (NULL);
	plane = ft_calloc(1, sizeof(t_plane));
	if (!plane)
		return (panic(NULL, NULL, -1), NULL);
	plane->type = PLANE;
	plane->position = strtocoord(props[1]);
	plane->vector = strtocoord(props[2]);
	plane->color = strtorgb(props[3]);
	return ((t_object *)plane);
}

t_object	*parse_cylinder(char **props, int line)
{
	t_cylinder	*cylinder;

	if (!validate_props(props, "PVFFR", line))
		return (NULL);
	cylinder = ft_calloc(1, sizeof(t_cylinder));
	if (!cylinder)
		return (panic(NULL, NULL, -1), NULL);
	cylinder->type = CYLINDER;
	cylinder->position = strtocoord(props[1]);
	cylinder->vector = strtocoord(props[2]);
	cylinder->color = strtorgb(props[3]);
	cylinder->diameter = strtofloat(props[4]);
	cylinder->height = strtofloat(props[5]);
	return ((t_object *)cylinder);
} */