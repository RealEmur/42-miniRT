/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 10:37:19 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/17 03:38:22 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_texture	*get_texture(t_texture *textures, int side, \
double ray_x, double ray_y)
{
	if (side == 0 && ray_x > 0)
		return (&textures[WEST]);
	else if (side == 0 && ray_x < 0)
		return (&textures[EAST]);
	else if (side == 1 && ray_y > 0)
		return (&textures[SOUTH]);
	else
		return (&textures[NORTH]);
}
