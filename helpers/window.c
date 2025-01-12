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
	ray.direction = Vector_normalize(Vector_add(factors, ((t_camera *)ft_lstfind(scene->objects, CAMERA))->vector));
	return (ray);
}


bool intersect(t_ray *ray, t_list *triangles)
{
	t_triangle *triangle;
	(void)ray;
	while (triangles)
	{
		triangle = triangles->content;
		triangles = triangles->next;
	}
	return (false);
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
			factors = canvas_to_viewport(coord.x, coord.y, scene);
			ray = create_ray(scene, factors);
			if (intersect(&ray, scene->triangles))
			{

			}
				/* closest.color = calculate_lightning(scene, &closest) */
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
	t_scene *scene = (t_scene *) s;
	if (scene->render_mode == RERENDER_REQUIRED)
	{
		reset_canvas(scene->canvas);
		render(scene);
	}
	mlx_put_image_to_window(scene->mlx, scene->mlx_win, scene->canvas, 0, 0);
	return (0);
}

// double my_fabs(double x) {
//     if (x < 0) {
//         return -x;  // Return the negative of x if x is negative
//     }
//     return x;  // Return x if it's already positive or zero
// }

// void draw_line(t_scene *scene, t_coords p1, t_coords p2, int color) {
//     int dx = p2.x - p1.x;
//     int dy = p2.y - p1.y;
//     int steps;
//     float x_increment, y_increment;
//     float x = p1.x;
//     float y = p1.y;

//     steps = my_fabs(dx) > my_fabs(dy) ? my_fabs(dx) : my_fabs(dy);
//     x_increment = dx / (float)steps;
//     y_increment = dy / (float)steps;

//     for (int i = 0; i <= steps; i++) {
//         mlx_pixel_put(scene->mlx, scene->mlx_win, round(x), round(y), color);
//         x += x_increment;
//         y += y_increment;
//     }
// }

// void draw_triangle(t_scene *scene, t_triangle *triangle) {
//     draw_line(scene, triangle->p1, triangle->p2, 0xFFFFFF); // Beyaz renk
//     draw_line(scene, triangle->p2, triangle->p3, 0xFFFFFF);
//     draw_line(scene, triangle->p3, triangle->p1, 0xFFFFFF);
// }

void    init_mlx(t_scene *scene)
{
    scene->mlx = mlx_init();
	scene->mlx_win = mlx_new_window(scene->mlx, WIDTH, HEIGHT, "Hello world!");
	scene->canvas = mlx_new_image(scene->mlx, WIDTH, HEIGHT);
	// t_list *tmp = scene->triangles;
	// while (tmp)
	// {
	// 	draw_triangle(scene, tmp->content);
	// 	tmp = tmp->next;
	// }
	render(scene);
	scene->render_mode = NOTHING;
	mlx_loop_hook(scene->mlx, render_next_frame, scene);
	mlx_loop(scene->mlx);
} 	