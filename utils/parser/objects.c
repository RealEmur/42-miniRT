/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:17:58 by emyildir          #+#    #+#             */
/*   Updated: 2024/12/28 18:59:43 by emyildir         ###   ########.fr       */
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
	camera->position = strtocoords(props[1]);
	camera->vector	= strtocoords(*vector);
	camera->fov	= ft_atoi(props[3]);
	return ((t_object *)camera);
}