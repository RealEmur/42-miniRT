/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:17:58 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/05 17:49:11 by emyildir         ###   ########.fr       */
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
		if (identifier == 'F' && !is_float(props[i]))
			return (parser_panic(line, props[i], ERR_ARG_FLOAT), false);
		if (identifier == 'R' && !is_rgb(props[i]))
			return (parser_panic(line, props[i], ERR_ARG_RGB), false);
		if (identifier == 'R' && !validate_rgb(strtorgb(props[i])))
			return (parser_panic(line, props[i], ERR_RGB_RANGE), false);
		if ((identifier == 'P' || identifier == 'V') && !is_coord(props[i]))
			return (parser_panic(line, props[i], ERR_ARG_COORDINATE), false);
		if (identifier == 'V' && !validate_vector(strtocoord(props[i])))
			return (parser_panic(line, props[i], ERR_ARG_COORDINATE), false);
		if (identifier == 'N' && !is_num(props[i]))
			return (parser_panic(line, props[i], ERR_ARG_INTEGER), false);
	}
	return (1);
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