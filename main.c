/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:16:39 by emyildir          #+#    #+#             */
/*   Updated: 2024/12/28 19:02:14 by emyildir         ###   ########.fr       */
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
		t_object_types	const type = ((t_object *) objlist->content)->type;
		if (type == AMBIENT_LIGHTNING)
		{
			t_ambient	*ambient = objlist->content; 
			printf("%d - AMBIENT LIGHTNING: Light Ratio: %f RGB: %d,%d,%d\n",i, ambient->light_ratio,ambient->color.red,ambient->color.blue,ambient->color.blue);
		}
		if (type == CAMERA)
		{
			t_camera	*camera = objlist->content; 
			printf("%d - CAMERA: Position: (%.2f,%.2f,%.2f) Vector: (%.2f,%.2f,%.2f) Fov: %d\n",i, camera->position.x, camera->position.y, camera->position.z, camera->vector.x, camera->vector.y, camera->vector.z, camera->fov);
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