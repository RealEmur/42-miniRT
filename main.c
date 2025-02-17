/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:16:39 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/17 19:28:25 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
