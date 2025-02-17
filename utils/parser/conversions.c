/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 15:25:05 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/17 18:05:41 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	is_rgb_int_range(char *str)
{
	int		diff;
	char	*temp;
	char	*comma;

	while (str)
	{
		temp = ft_itoa(ft_atoi(str));
		if (!temp)
			return (false);
		comma = ft_strchr(str, ',');
		if (comma)
			diff = ft_strncmp(temp, str, comma - str);
		else
			diff = ft_strncmp(temp, str, ft_strlen(str));
		free(temp);
		if (diff)
			return (false);
		if (!comma)
			break ;
		str = comma + 1;
	}	
	return (true);
}

int	is_num(char *str)
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

int	is_rgb(char *str)
{
	int			i;
	int			is_rgb;
	const int	size = ft_strlen(str);
	char		**splitted;

	if (ft_strnstr(str, ",,", size)
		|| (*str == ',' || str[size - 1] == ','))
		return (false);
	is_rgb = true;
	splitted = ft_split(str, ',');
	if (!splitted)
		return (false);
	if (str_arr_size(splitted) != 3)
		is_rgb = false;
	i = -1;
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

int	rgbtouint(t_rgb rgb)
{
	return (rgb.red * 65536 + rgb.green * 256 + rgb.blue);
}
