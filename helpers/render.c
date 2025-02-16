/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 08:50:26 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/16 16:54:41 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	paint_wall(t_scene *scene, t_ray *ray, double wall_x, int side)
{
	t_texture	*texture;
	int			tex_x;
	int			draw_y;
	double		step;
	double		texpos;

	texture = get_texture(scene->options.textures, \
	side, ray->dir.x, ray->dir.y);
	tex_x = (int)(wall_x * (double)(texture->width));
	if ((side == 1 && ray->dir.y < 0)
		|| (side == 0 && ray->dir.x > 0))
		tex_x = texture->width - tex_x - 1;
	step = (double)texture->height / ray->height ;
	texpos = (ray->draw_start - (HEIGHT / 2) + (ray->height / 2)) * step;
	draw_y = ray->draw_start;
	while (draw_y < ray->draw_end)
	{
		texpos += step;
		draw_pixel(&scene->mlx.image, ray->current_x, draw_y++, \
		get_pixel_color(&texture->image, tex_x, \
		(int)texpos & (texture->height - 1)));
	}
}

int	wall_hit(t_scene *scene, t_ray *ray, t_position *pos, int side)
{
	double	wall_x;
	double	wall_dist;

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
	paint_wall(scene, ray, wall_x, side);
	return (1);
}

void	send_ray(t_scene *scene, t_ray *ray, t_position *pos)
{
	int				map_x;
	int				map_y;
	int				side_hit;
	char **const	layout = scene->map.layout;

	map_x = (int)pos->x;
	map_y = (int)pos->y;
	while (layout[map_y][map_x] != WALL_CHAR)
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
	}
	wall_hit(scene, ray, pos, side_hit);
}

void	init_ray(t_ray *ray, t_position *pos, t_vector *direction, \
t_vector *plane)
{
	const double	camera_x = 2 * ray->current_x / (double)WIDTH - 1;

	ray->dir.x = direction->x + plane->x * camera_x;
	ray->dir.y = direction->y + plane->y * camera_x;
	ray->deltadistx = 1e30;
	if (ray->dir.x != 0)
		ray->deltadistx = fabs(1 / ray->dir.x);
	ray->deltadisty = 1e30;
	if (ray->dir.y != 0)
		ray->deltadisty = fabs(1 / ray->dir.y);
	ray->step_x = 1;
	ray->sidedistx = ((int)pos->x + 1.0 - pos->x) * ray->deltadistx;
	if (ray->dir.x < 0)
	{
		ray->step_x = -1;
		ray->sidedistx = (pos->x - (int)pos->x) * ray->deltadistx;
	}
	ray->step_y = 1;
	ray->sidedisty = ((int)pos->y + 1.0 - pos->y) * ray->deltadisty;
	if (ray->dir.y < 0)
	{
		ray->step_y = -1;
		ray->sidedisty = (pos->y - (int)pos->y) * ray->deltadisty;
	}
}

void	render(t_scene *scene)
{
	t_ray *const	ray = &(t_ray){0};
	t_image *const	image = &scene->mlx.image;
	t_player *const	player = &scene->player;
	t_vector *const	direction = &player->direction;
	t_vector *const	plane = &player->plane;

	draw_background(image, scene->options.colors);
	ray->current_x = -1;
	while (++ray->current_x < WIDTH)
	{
		init_ray(ray, &player->position, direction, plane);
		send_ray(scene, ray, &player->position);
	}
	mlx_put_image_to_window(scene->mlx.mlx, scene->mlx.win, image->img, 0, 0);
}
