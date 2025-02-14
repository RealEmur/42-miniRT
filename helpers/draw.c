/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:02:19 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/14 09:25:23 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

