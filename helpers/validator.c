/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:29:14 by emyildir          #+#    #+#             */
/*   Updated: 2024/12/28 19:50:46 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	validate_rgb(t_rgb *rgb)
{
	if ((rgb->red < 0 || rgb->red > 255) 
		|| (rgb->green < 0 || rgb->green > 255)
		|| (rgb->blue < 0 || rgb->blue > 255))
		return (false);
	return (true);
}

int	validate_vector(t_vector *vector, float min, float max)
{
	if ((vector->x < min || vector->x > max) 
		|| (vector->y < min || vector->y > max)
		|| (vector->z < min || vector->z > max))
		return (false);
	return (true);
}

int	validate_ambient(t_ambient	*ambient_light)
{
	if (ambient_light->light_ratio < 0 
	|| ambient_light->light_ratio > 1)
		return (panic("Ambient Lightning", "Lightning ratio must be in range 0.0,1.0", false));
	if (!validate_rgb(&ambient_light->color))
		return (panic("Ambient Lightning", "RGB Values must be in range 0,255", false));
	return (true);	
}

int	validate_camera(t_camera	*camera)
{
	if (!validate_vector(&camera->vector, -1, 1))
		return (panic("Camera", "Orientation vector values must be in range -1,1", false));
	if (camera->fov > 180 || camera->fov < 0)
		return (panic("Camera", "FOV must be in range 0,180", false));
	return (true);
}

int	validate_light(t_light	*light)
{
	if (light->brightness < 0 
	|| light->brightness > 1)
		return (panic("Light", "Lightning ratio must be in range 0.0,1.0", false));
	if (!validate_rgb(&light->color))
		return (panic("Light", "RGB Values must be in range 0,255", false));
	return (true);
}

int validate_sphere(t_sphere *sphere)
{
	if (!validate_rgb(&sphere->color))
		return (panic("Sphere", "RGB Values must be in range 0,255", false));
	return (true);
}

int validate_plane(t_plane *plane)
{
	if (!validate_vector(&plane->vector, -1, 1))
		return (panic("Plane", "Orientation vector values must be in range -1,1", false));
	if (!validate_rgb(&plane->color))
		return (panic("Plane", "RGB Values must be in range 0,255", false));
	return (true);
}

int validate_cylinder(t_cylinder *cylinder)
{
	if (!validate_vector(&cylinder->vector, -1, 1))
		return (panic("Cylinder", "Orientation vector values must be in range -1,1", false));
	if (!validate_rgb(&cylinder->color))
		return (panic("Cylinder", "RGB Values must be in range 0,255", false));
	return (true);
}

int	validator(t_list	*objlist)
{
	t_object		*obj;
	t_object_types	type;
	
	while (objlist)
	{
		obj = objlist->content;
		type = obj->type;
		
		if ((type == AMBIENT_LIGHTNING && !validate_ambient((t_ambient *) obj))
			|| (type == CAMERA && !validate_camera((t_camera *)obj)) 
			|| (type == LIGHT && !validate_light((t_light *)obj)) 
			|| (type == SPHERE && !validate_sphere((t_sphere *)obj))
			|| (type == PLANE && !validate_plane((t_plane *)obj))
			|| (type == CYLINDER && !validate_cylinder((t_cylinder *)obj))
			)
			return (false);
		objlist = objlist->next;
	}
	return (true);
}