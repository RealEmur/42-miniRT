/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tugcekul <tugcekul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 18:49:39 by tkul              #+#    #+#             */
/*   Updated: 2025/01/11 20:28:06 by tugcekul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

t_object *ft_lstfind(t_list *lst, t_object_types type)
{
	while (lst)
	{
		t_object *object = lst->content;
		if (object->type == type)
			return (object);
		lst = lst->next;
	}
	return (NULL);
}

t_vector Vector_add(t_vector a, t_vector b)
{
	t_vector result;
	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vector Vector_normalize(t_vector v)
{
	float len = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	t_vector result;
	result.x = v.x / len;
	result.y = v.y / len;
	result.z = v.z / len;
	return (result);
}
void init_viewport(t_scene *scene)
{
	t_camera *camera = (t_camera *)ft_lstfind(scene->objects, CAMERA);
	if (!camera)
		panic("Scene", "No camera found", -1);
	scene->viewport.width = tan(RADIAN(camera->fov) / 2);
	scene->viewport.height = scene->viewport.width * 9 / 16;
}

t_vector canvas_to_viewport(int x, int y, t_scene *s) {
    t_vector viewport_coords;

    viewport_coords.x = ((2.0 * x) / WIDTH - 1) * s->viewport.width;
    viewport_coords.y = ((2.0 * y) / HEIGHT - 1) * s->viewport.height;
    viewport_coords.z = 1;
    return (viewport_coords);
}


t_ray create_ray(t_scene *scene, t_vector factors)
{
	t_ray ray;
	ray.origin = ((t_camera *)ft_lstfind(scene->objects, CAMERA))->position;
	// printf("Camera position: %f, %f, %f\n", ray.origin.x, ray.origin.y, ray.origin.z);
	ray.direction = Vector_normalize(Vector_add(factors, ((t_camera *)ft_lstfind(scene->objects, CAMERA))->vector));
	// printf("Ray direction: %f, %f, %f\n", ray.direction.x, ray.direction.y, ray.direction.z);
	return (ray);
}

void	render(t_scene *scene)
{
	t_vector factors;
	t_vector coord;
	t_ray ray;
	t_hit closest;

	init_viewport(scene);
	coord.y = -1;
	while (++coord.y < HEIGHT)
	{
		coord.x = -1;
		while (++coord.x < WIDTH)
		{
			closest.t = INFINITY;
			closest.object = NULL;
			closest.color = BLACK;
			t_list *objects = scene->objects;
			factors = canvas_to_viewport(coord.x, coord.y, scene);
			// printf("Factors: %f, %f, %f\n", factors.x, factors.y, factors.z);
			ray = create_ray(scene, factors);
			// if (intersect(&ray, &closest, objects))
			// 	closest.color = calculate_lightning(scene, &closest)
			(void)objects;
			(void)ray;
			(void)closest;
		}
	}
}

void reset_canvas(void *canvas)
{
	int i = 0;
	int j = 0;
	int *img = (int *)mlx_get_data_addr(canvas, &i, &j, &j);
	while(i < WIDTH)
	{
		j = 0;
		while(j < HEIGHT)
		{
			img[j * WIDTH + i] = 0x000000;
			j++;
		}
		i++;
	}
}

int	render_next_frame(void *s)
{
	t_scene *scene = (t_scene *)s;
	reset_canvas(scene->canvas);
	render(scene);
	mlx_put_image_to_window(scene->mlx, scene->mlx_win, scene->canvas, 0, 0);
	return (0);
}

void    init_mlx(t_scene *scene)
{
    scene->mlx = mlx_init();
	scene->mlx_win = mlx_new_window(scene->mlx, WIDTH, HEIGHT, "Hello world!");
	void *canvas = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	scene->canvas = canvas; 
	mlx_loop_hook(scene->mlx, render_next_frame, scene);
	mlx_loop(scene->mlx);
} 	