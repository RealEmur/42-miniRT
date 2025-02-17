/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:16:39 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/17 18:07:14 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_all(t_scene *scene)
{
	int					i;
	t_mlx *const		mlx = &scene->mlx;
	t_texture *const	textures = scene->options.textures;

	if (scene->map.layout)
		free_str_arr(scene->map.layout);
	i = -1;
	while (++i < TEXTURE_COUNT)
	{
		free(textures[i].path);
		if (mlx->mlx && textures[i].image.img)
			mlx_destroy_image(mlx->mlx, textures[i].image.img);
	}
	if (mlx->mlx && mlx->image.img)
		mlx_destroy_image(mlx->mlx, mlx->image.img);
	i = -1;
	while (++i < COLOR_COUNT)
		free(scene->options.colors[i]);
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->mlx)
		mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	ft_lstclear(&scene->pressed_keys, free);
}

void	set_player_data(t_player *player)
{
	t_vector *const	plane = &player->plane;
	t_vector *const	direction = &player->direction;

	if (player->initial_direction == EAST)
	{
		direction->x = -1;
		plane->y = 0.66;
	}
	else if (player->initial_direction == WEST)
	{
		direction->x = 1;
		plane->y = -0.66;
	}
	else if (player->initial_direction == NORTH)
	{
		direction->y = -1;
		plane->x = -0.66;
	}
	else if (player->initial_direction == SOUTH)
	{
		direction->y = 1;
		plane->x = 0.66;
	}
}

int	main(int size, char **args)
{
	t_scene *const	scene = &(t_scene){0};

	if (size == 2)
	{
		if (!parser(args[1], scene))
			return (clean_all(scene), EXIT_FAILURE);
		set_player_data(&scene->player);
		init_display(scene);
		clean_all(scene);
	}
	else
		return (panic("Usage", ERR_USAGE, EXIT_FAILURE));
	return (EXIT_SUCCESS);
}
