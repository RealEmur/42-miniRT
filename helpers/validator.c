/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:29:14 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/05 17:51:52 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minirt.h"

int	validate_rgb(t_rgb rgb)
{
	if ((rgb.red < 0 || rgb.red > 255) 
		|| (rgb.green < 0 || rgb.green > 255)
		|| (rgb.blue < 0 || rgb.blue > 255))
		return (false);
	return (true);
}

int	validate_vector(t_vector vector)
{
	if ((vector.x < -1.0 || vector.x > 1.0) 
		|| (vector.y < -1.0 || vector.y > 1.0)
		|| (vector.z < -1.0 || vector.z > 1.0))
		return (false);
	return (true);
}


int	validator(t_list	*objlist)
{
	(void) objlist;
	return (true);
}