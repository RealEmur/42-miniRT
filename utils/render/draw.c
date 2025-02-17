/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:04:23 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/17 03:37:44 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	get_pixel_index(t_image	*image, int x, int y)
{
	return ((y * image->size_line + x * (image->bpp / 8)) / 4);
}

unsigned int	get_pixel_color(t_image *image, int x, int y)
{
	unsigned int *const	addr = (unsigned int *)image->addr;
	const int			pos = get_pixel_index(image, x, y);

	return (addr[pos]);
}

void	draw_pixel(t_image	*image, int x, int y, unsigned int color)
{
	unsigned int *const	addr = (unsigned int *)image->addr;
	const int			pos = get_pixel_index(image, x, y);

	addr[pos] = color;
}

void	draw_background(t_image *image, t_rgb	**rgbs)
{
	int				y;
	int				x;
	unsigned int	color;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			if (y <= HEIGHT / 2)
				color = rgbtouint(*rgbs[CEILING_COLOR]);
			else
				color = rgbtouint(*rgbs[FLOOR_COLOR]);
			draw_pixel(image, x, y, color);
		}
	}
}
