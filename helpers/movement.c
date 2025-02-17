/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 02:28:34 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/17 03:24:36 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	is_walkable(t_map *map, int x, int y)
{
	char **const	layout = map->layout;

	if (x < 0 || x >= map->width || y < 0 || y >= map->height)
		return (false);
	return (ft_strchr(MOVEABLE_CHARS, layout[y][x]) || false);
}

void	move_player(t_player *player, t_map *map, double dist_x, double dist_y)
{
	t_position *const		pos = &player->position;
	const double			new_x = pos->x + dist_x;
	const double			new_y = pos->y + dist_y;

	if (is_walkable(map, pos->x, floor(new_y)))
		pos->y = new_y;
	if (is_walkable(map, floor(new_x), pos->y))
		pos->x = new_x;
}

void	rotate_player(t_player *player, double angle)
{
	t_vector *const		dir = &player->direction;
	t_vector *const		plane = &player->plane;
	const double		olddir_x = dir->x;
	const double		oldplane_x = plane->x;

	dir->x = olddir_x * cos(angle) - dir->y * sin(angle);
	dir->y = olddir_x * sin(angle) + dir->y * cos(angle);
	plane->x = oldplane_x * cos(angle) - plane->y * sin(angle);
	plane->y = oldplane_x * sin(angle) + plane->y * cos(angle);
}

void	player_movement(t_scene *scene, t_player *player, double delta_time)
{
	t_list *const	pressed_keys = scene->pressed_keys;
	t_vector *const	dir = &player->direction;
	const double	speed = delta_time * MOVE_SPEED;
	const double	angle = delta_time * 180 * ROTATION_SPEED * M_PI / 180.0;

	if (is_key_pressed(pressed_keys, KEY_ESC))
		close_window(scene);
	if (is_key_pressed(pressed_keys, KEY_W))
		move_player(player, &scene->map, dir->x * speed, dir->y * speed);
	if (is_key_pressed(pressed_keys, KEY_S))
		move_player(player, &scene->map, -dir->x * speed, -dir->y * speed);
	if (is_key_pressed(pressed_keys, KEY_A))
		move_player(player, &scene->map, -dir->y * speed, dir->x * speed);
	if (is_key_pressed(pressed_keys, KEY_D))
		move_player(player, &scene->map, dir->y * speed, -dir->x * speed);
	if (is_key_pressed(pressed_keys, KEY_LEFT))
		rotate_player(player, angle);
	if (is_key_pressed(pressed_keys, KEY_RIGHT))
		rotate_player(player, -angle);
}
