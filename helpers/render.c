/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:50:26 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/14 11:38:23 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void paint_wall(t_scene *scene, t_ray *ray, int wall_x, int side)
{
	t_texture *texture = get_texture(scene->options.textures, side, ray->dir.x, ray->dir.y);
	int tex_x = (int)(wall_x * (double)(texture->width));
	double step;
	double texPos;
	
	if (side == 0 && ray->dir.x > 0)
		tex_x = texture->width - tex_x - 1;
	if (side == 1 && ray->dir.x < 0)
		tex_x = texture->width - tex_x - 1;
	step = (double)texture->height / ray->height ;
	texPos = (ray->draw_start - (HEIGHT / 2) + (ray->height  / 2)) * step;
	for (int y = ray->draw_start; y < ray->draw_end; y++)
	{
		int tex_y = (int)texPos & (texture->height - 1);
		texPos += step;
		unsigned int index = y * WIDTH + ray->current_x;
		((unsigned int *)scene->mlx.image.addr)[index] = ((unsigned int *)texture->image.addr)[texture->width * tex_y + tex_x];
	}
}

int wall_hit(t_scene *scene, t_ray *ray, t_position *pos, int side)
{
	double wall_x;
	double wall_dist;
	
	if (side == 0)
		wall_dist = (ray->sidedistx - ray->deltadistx);
	else
		wall_dist = (ray->sidedisty - ray->deltadisty);
	ray->height = (int)(HEIGHT / wall_dist);
	ray->draw_start = -ray->height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	if (side == 0)
		wall_x = pos->y + wall_dist * ray->dir.y;
	else
		wall_x = pos->x + wall_dist * ray->dir.x;
	wall_x -= floor(wall_x);
	paint_wall(scene,ray,wall_x,side);
	return (1);
}

void send_ray(t_scene *scene, t_ray *ray, t_position *pos)
{
	int map_x;
	int map_y;
	int side_hit;
	
	char **const layout = scene->map.layout;

	map_x = (int)pos->x;
	map_y = (int)pos->y;
	while (1)	
	{
		if (ray->sidedistx < ray->sidedisty)
		{
			ray->sidedistx += ray->deltadistx;
			map_x += ray->step_x;
			side_hit = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			map_y += ray->step_y;
			side_hit = 1;
		}
		if (layout[map_y][map_x] == WALL_CHAR)
		{
			wall_hit(scene, ray, pos, side_hit);
			break;
		}
	}
}

void calc_ray_distances(t_ray *ray, t_position *pos)
{
    ray->deltadistx = 1e30;
    if (ray->dir.x != 0)
        ray->deltadistx = fabs(1 / ray->dir.x);
    ray->deltadisty = 1e30;
    if (ray->dir.y != 0)
        ray->deltadisty = fabs(1 / ray->dir.y);

    if (ray->dir.x < 0)
    {
        ray->step_x = -1;
        ray->sidedistx = (pos->x - (int)pos->x) * ray->deltadistx;
    }
    else
    {
        ray->step_x = 1; // Düzeltme: step_x pozitif yönde 1 olmalı
        ray->sidedistx = ((int)pos->x + 1.0 - pos->x) * ray->deltadistx;
    }

    if (ray->dir.y < 0)
    {
        ray->step_y = -1;
        ray->sidedisty = (pos->y - (int)pos->y) * ray->deltadisty;
    }
    else
    {
        ray->step_y = 1; // Düzeltme: step_y pozitif yönde 1 olmalı
        ray->sidedisty = ((int)pos->y + 1.0 - pos->y) * ray->deltadisty;
    }
}
void create_rays(t_scene *scene, t_position *pos, t_vector *dirs, t_vector *plane)
{
	int camera_x;
	t_ray *ray = &(t_ray){0};

	ray->current_x = -1;
	while (++ray->current_x < WIDTH)
	{
		camera_x = 2 * ray->current_x / (double)WIDTH - 1;
		ray->dir.x = dirs->x + plane->x * camera_x;
		ray->dir.y = dirs->y + plane->y * camera_x;
		calc_ray_distances(ray, pos);
		printf("%f %f\n", dirs->x, dirs->y);
		send_ray(scene, ray, pos);
	}
}

void render(t_scene *scene)
{
	t_image *const image = &scene->mlx.image;
	t_player *const player = &scene->player;

	draw_background(image, scene->options.colors);
	create_rays(scene, &player->position, &player->direction, &player->plane);
	mlx_put_image_to_window(scene->mlx.mlx, scene->mlx.win, image->img, 0, 0);
}