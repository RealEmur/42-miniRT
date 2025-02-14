/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 09:04:23 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/14 09:16:48 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void draw_pixel(t_image	*image, int x, int y, unsigned int color)
{
	unsigned int	*addr = (unsigned int *)image->addr;
	const int		pos = (y * image->size_line + x * (image->bpp / 8)) / 4;
	
	addr[pos]= color;
}