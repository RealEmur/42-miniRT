/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:17:58 by emyildir          #+#    #+#             */
/*   Updated: 2024/12/28 19:21:23 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

t_object	*parse_ambient_lightning(char **props)
{
	t_ambient	*ambient; 
	char		**const light_ratio = props + 1;
	char		**const rgb = props + 2;
	
	if (str_arr_size(props) != 3 
		|| !is_float(*light_ratio)
		|| !is_rgb(*rgb))
		return (panic("Scene File", ERR_SCENE_FORMAT, -1), NULL);
	ambient = ft_calloc(1, sizeof(t_ambient));
	if (!ambient)
		return (panic(NULL, NULL, -1), NULL);
	ambient->type = AMBIENT_LIGHTNING;
	ambient->light_ratio = strtofloat(*light_ratio);
	ambient->color = strtorgb(*rgb);
	return ((t_object *)ambient);
}

t_object	*parse_camera(char **props)
{
	t_camera	*camera;
	char		**const	position = props + 1; 
	char		**const vector = props + 2;
	char		**const	fov = props + 3;
	
	if (str_arr_size(props) != 4
		|| !is_coord(*position)
		|| !is_coord(*vector)
		|| !is_num(*fov))
		return (panic("Scene File", ERR_SCENE_FORMAT, -1), NULL);
	camera = ft_calloc(1, sizeof(t_camera));
	if (!camera)
		return (panic(NULL, NULL, -1), NULL);
	camera->type = CAMERA;
	camera->position = strtocoords(*position);
	camera->vector	= strtocoords(*vector);
	camera->fov	= ft_atoi(*fov);
	return ((t_object *)camera);
}

t_object	*parse_light(char **props)
{
	t_light	*light;
	char		**const	position = props + 1; 
	char		**const brightness = props + 2;
	char		**const	color = props + 3;
	
	if (str_arr_size(props) != 4
		|| !is_coord(*position)
		|| !is_float(*brightness)
		|| !is_rgb(*color))
		return (panic("Scene File", ERR_SCENE_FORMAT, -1), NULL);
	light = ft_calloc(1, sizeof(t_light));
	if (!light)
		return (panic(NULL, NULL, -1), NULL);
	light->type = LIGHT;
	light->position = strtocoords(*position);
	light->brightness = strtofloat(*brightness);
	light->color = strtorgb(*color);
	return ((t_object *)light);
}

t_object	*parse_sphere(char **props)
{
	t_sphere	*sphere;
	char		**const	position = props + 1; 
	char		**const diameter = props + 2;
	char		**const	color = props + 3;
	
	if (str_arr_size(props) != 4
		|| !is_coord(*position)
		|| !is_float(*diameter)
		|| !is_rgb(*color))
		return (panic("Scene File", ERR_SCENE_FORMAT, -1), NULL);
	sphere = ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		return (panic(NULL, NULL, -1), NULL);
	sphere->type = SPHERE;
	sphere->position = strtocoords(*position);
	sphere->diameter = strtofloat(*diameter);
	sphere->color = strtorgb(*color);
	return ((t_object *)sphere);
}

t_object	*parse_plane(char **props)
{
	t_plane	*plane;
	char		**const	position = props + 1; 
	char		**const vector = props + 2;
	char		**const	color = props + 3;
	
	if (str_arr_size(props) != 4
		|| !is_coord(*position)
		|| !is_coord(*vector)
		|| !is_rgb(*color))
		return (panic("Scene File", ERR_SCENE_FORMAT, -1), NULL);
	plane = ft_calloc(1, sizeof(t_plane));
	if (!plane)
		return (panic(NULL, NULL, -1), NULL);
	plane->type = PLANE;
	plane->position = strtocoords(*position);
	plane->vector = strtocoords(*vector);
	plane->color = strtorgb(*color);
	return ((t_object *)plane);
}

t_object	*parse_cylinder(char **props)
{
	t_cylinder	*cylinder;
	char		**const	position = props + 1; 
	char		**const vector = props + 2;
	char		**const diameter = props + 3;
	char		**const height = props + 4;
	char		**const	color = props + 5;
	
	if (str_arr_size(props) != 6
		|| !is_coord(*position)
		|| !is_coord(*vector)
		|| !is_rgb(*color))
		return (panic("Scene File", ERR_SCENE_FORMAT, -1), NULL);
	cylinder = ft_calloc(1, sizeof(t_cylinder));
	if (!cylinder)
		return (panic(NULL, NULL, -1), NULL);
	cylinder->type = CYLINDER;
	cylinder->position = strtocoords(*position);
	cylinder->vector = strtocoords(*vector);
	cylinder->color = strtorgb(*color);
	cylinder->diameter = strtofloat(*diameter);
	cylinder->height = strtofloat(*height);
	return ((t_object *)cylinder);
}