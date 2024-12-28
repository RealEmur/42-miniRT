/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:25:05 by emyildir          #+#    #+#             */
/*   Updated: 2024/12/28 19:08:43 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int		is_coord(char *str)
{
	int		i;
	int		is_vector;
	char	**splitted;
	
	if (ft_strnstr(str, ",,", ft_strlen(str)))
		return (false);
	i = -1;
	is_vector = true;
	splitted = ft_split(str, ',');
	if (!splitted)
		return (false);
	if (str_arr_size(splitted) != 3)
		is_vector = false;
	while (is_vector && splitted[++i])
		if (!is_float(splitted[i]))
			is_vector = false;
	free_str_arr(splitted);
	return (is_vector);
}

t_coords	strtocoords(char *str)
{
	t_coords	coords;

	ft_memset(&coords, 0, sizeof(t_coords));
	coords.x = strtofloat(str);
	str = ft_strnstr(str, ",", ft_strlen(str));
	if (!str)
		return (coords);
	coords.y = strtofloat(++str);
	str = ft_strnstr(str, ",", ft_strlen(str));
	if (!str)
		return (coords);
	coords.z = strtofloat(++str);
	return (coords);
}


int		is_num(char *str)
{
	int		i;

	if (!str)
		return (false);
	if (*str == '-' || *str == '+')
		str++;
	i = 0;
	while (ft_isdigit(str[i]))
		i++;
	return (!str[i] && i > 0);
}

int		is_rgb(char *str)
{
	int		i;
	int		is_rgb;
	char	**splitted;
	
	if (ft_strnstr(str, ",,", ft_strlen(str)))
		return (false);
	i = -1;
	is_rgb = true;
	splitted = ft_split(str, ',');
	if (!splitted)
		return (false);
	if (str_arr_size(splitted) != 3)
		is_rgb = false;
	while (is_rgb && splitted[++i])
		if (!is_num(splitted[i]))
			is_rgb = false;
	free_str_arr(splitted);
	return (is_rgb);
}

t_rgb	strtorgb(char *str)
{
	t_rgb	rgb;

	ft_memset(&rgb, 0, sizeof(t_rgb));
	rgb.red = ft_atoi(str);
	str = ft_strnstr(str, ",", ft_strlen(str));
	if (!str)
		return (rgb);
	rgb.green = ft_atoi(++str);
	str = ft_strnstr(str, ",", ft_strlen(str));
	if (!str)
		return (rgb);
	rgb.blue = ft_atoi(++str);
	return (rgb);
}

int		is_float(char *str)
{
	int		i;

	if (!str)
		return (false);
	if (*str == '-' || *str == '+')
		str++;
	i = 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] && str[i++] != '.')
		return (false);
	str = str + i;
	i = 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	return (!str[i] || (str[i] == '.' && i == 0));
}

float strtofloat(char *str)
{
	int		i;
	int		divider;
	int		sign;
	float	num;
	
	num = 0.0;
	sign = 1;
	i = 0;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (ft_isdigit(str[i]))
		num = (num * 10) + str[i++] - '0';
	if (str[i] == '.') {
		i++;
		divider = 10;
		while (ft_isdigit(str[i])) {
			num += ((float)(str[i++] - '0')) / divider;
			divider *= 10;
		}
	}
	return (num * sign);
}