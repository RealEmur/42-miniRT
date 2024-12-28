/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:16:39 by emyildir          #+#    #+#             */
/*   Updated: 2024/12/28 19:25:06 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int panic(char *tag, char *error, int rtrn_val)
{
    ft_putendl_fd("Error", STDERR_FILENO);
    if (error)
	{
		ft_putstr_fd(tag, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
        ft_putendl_fd(error, STDERR_FILENO);
	}
	else
		perror(tag);
    return (rtrn_val);
}

void	print_objects(t_list *objlist)
{
	int		i = 0;
	
	while (objlist)
	{
		t_object_types const type = ((t_object *) objlist->content)->type;

		if (type == AMBIENT_LIGHTNING)
		{
			t_ambient *ambient = objlist->content;
			printf("%d - AMBIENT LIGHTNING: Light Ratio: %.2f RGB: %d,%d,%d\n", 
				i, ambient->light_ratio, ambient->color.red, ambient->color.green, ambient->color.blue);
		}
		else if (type == CAMERA)
		{
			t_camera *camera = objlist->content;
			printf("%d - CAMERA: Position: (%.2f,%.2f,%.2f) Vector: (%.2f,%.2f,%.2f) FOV: %d\n", 
				i, camera->position.x, camera->position.y, camera->position.z, 
				camera->vector.x, camera->vector.y, camera->vector.z, camera->fov);
		}
		else if (type == LIGHT)
		{
			t_light *light = objlist->content;
			printf("%d - LIGHT: Position: (%.2f,%.2f,%.2f) Brightness: %.2f RGB: %d,%d,%d\n", 
				i, light->position.x, light->position.y, light->position.z, 
				light->brightness, light->color.red, light->color.green, light->color.blue);
		}
		else if (type == SPHERE)
		{
			t_sphere *sphere = objlist->content;
			printf("%d - SPHERE: Position: (%.2f,%.2f,%.2f) Diameter: %.2f RGB: %d,%d,%d\n", 
				i, sphere->position.x, sphere->position.y, sphere->position.z, 
				sphere->diameter, sphere->color.red, sphere->color.green, sphere->color.blue);
		}
		else if (type == PLANE)
		{
			t_plane *plane = objlist->content;
			printf("%d - PLANE: Position: (%.2f,%.2f,%.2f) Vector: (%.2f,%.2f,%.2f) RGB: %d,%d,%d\n", 
				i, plane->position.x, plane->position.y, plane->position.z, 
				plane->vector.x, plane->vector.y, plane->vector.z, 
				plane->color.red, plane->color.green, plane->color.blue);
		}
		else if (type == CYLINDER)
		{
			t_cylinder *cylinder = objlist->content;
			printf("%d - CYLINDER: Position: (%.2f,%.2f,%.2f) Vector: (%.2f,%.2f,%.2f) Diameter: %.2f Height: %.2f RGB: %d,%d,%d\n", 
				i, cylinder->position.x, cylinder->position.y, cylinder->position.z, 
				cylinder->vector.x, cylinder->vector.y, cylinder->vector.z, 
				cylinder->diameter, cylinder->height, 
				cylinder->color.red, cylinder->color.green, cylinder->color.blue);
		}
		else
		{
			printf("%d - UNKNOWN OBJECT TYPE\n", i);
		}
		i++;
		objlist = objlist->next;
	}
}


int main(int size, char **args)
{
	t_list	*objects;	
	
    if (size == 2)
    {
		objects = parser(args[1]);
		if (!objects)
			return (EXIT_FAILURE);
		print_objects(objects);
	}
    else 
        return (panic("Usage", ERR_USAGE, EXIT_FAILURE));
    return (EXIT_SUCCESS);
}