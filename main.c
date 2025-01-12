/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tugcekul <tugcekul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:16:39 by emyildir          #+#    #+#             */
/*   Updated: 2025/01/11 20:46:40 by tugcekul         ###   ########.fr       */
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
				i, ambient->brightness, ambient->color.red, ambient->color.green, ambient->color.blue);
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


t_list *ft_lstmerge(t_list *list1, t_list *list2)
{
    t_list *current;

    if (!list1)
        return list2;
    if (!list2)
        return list1;

    current = list1;
    while (current->next)
        current = current->next;
    current->next = list2;
    return (list1);
}

t_list *triangulate(t_list *objects)
{
    t_list *triangles;
    t_list *objects_copy;
	t_sphere	*sphere;
	t_cylinder *cylinder;
	t_plane *plane;

    triangles = NULL;
    objects_copy = objects;
    while (objects_copy)
	{
        if (((t_object *)objects_copy->content)->type == SPHERE)
		{
			sphere = objects_copy->content;
			triangulate_sphere(&triangles, (t_object *)sphere, sphere->position, sphere->diameter / 2, 5,5);
		}
		else if (((t_object *)objects_copy->content)->type == PLANE)
		{
			plane = objects_copy->content;
			triangulate_plane(&triangles, (t_object *)plane, plane->position, 10);
        }
		else if (((t_object *)objects_copy->content)->type == CYLINDER)
		{
			cylinder = objects_copy->content;
			triangulate_cylinder(&triangles, (t_object*)cylinder, cylinder->position, cylinder->diameter / 2, cylinder->height, 10, 10);
        }
        objects_copy = objects_copy->next;
    }
	return triangles;
}

int main(int size, char **args)
{
	t_list	*objects;
	t_scene	*const scene = &(t_scene){0};

    if (size == 2)
    {
		objects = parser(args[1]);
		if (!objects || !validator(objects))
			return (EXIT_FAILURE);
		scene->objects = objects;
		scene->triangles = triangulate(objects);
		display_scene(scene);
	}	
    else 
        return (panic("Usage", ERR_USAGE, EXIT_FAILURE));
    return (EXIT_SUCCESS);
}