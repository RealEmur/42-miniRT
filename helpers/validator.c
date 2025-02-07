/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 19:29:14 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/07 02:12:42 by emyildir         ###   ########.fr       */
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

int	validate_extension(char *path, char *extension)
{
	const int	len = ft_strlen(path) - 4;

	return (len >= 0 && !ft_strncmp(path + len, extension, 4));
}
