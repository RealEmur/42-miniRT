/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:16:39 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/07 15:29:55 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	clean_all(t_scene *scene)
{
	int		i;

	if (scene->map.layout)
		free_str_arr(scene->map.layout);
	i = -1;
	while (++i < TEXTURE_COUNT)
		free(scene->options.textures[i]);
	i = -1;
	while (++i < COLOR_COUNT)
		free(scene->options.colors[i]);
}

void	print_map(t_map *map)
{
	for (int i = 0; i < map->height; i++)
	{
		printf("%s\n", map->layout[i]);	
	}
}

int main(int size, char **args)
{
	t_scene	*const scene = &(t_scene){0};

    if (size == 2)
    {
		if (!parser(args[1], scene))
			return (clean_all(scene), EXIT_FAILURE);
		print_map(&scene->map);
	}	
    else 
        return (panic("Usage", ERR_USAGE, EXIT_FAILURE));
    return (EXIT_SUCCESS);
}