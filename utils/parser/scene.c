/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 14:15:51 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/05 14:38:16 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minirt.h"

int	is_valid_extension(char *path)
{
	const int	len = ft_strlen(path) - 3;

	return (len >= 0 && !ft_strncmp(path + len, MAP_FILE_EXTENSION, 4));
}