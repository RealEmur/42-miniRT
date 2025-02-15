/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:16:39 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/15 03:30:50 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clean_all(t_scene *scene)
{
	t_mlx *const 		mlx = &scene->mlx;
	t_rgb **const		colors = scene->options.colors;
	t_texture *const	textures = scene->options.textures;
	int		i;

	if (scene->map.layout)
		free_str_arr(scene->map.layout);
	i = -1;
	while (++i < TEXTURE_COUNT)
	{
		free(textures[i].path);
		if (mlx->mlx && textures[i].image.img)
			mlx_destroy_image(mlx->mlx, textures[i].image.img);
	}
	i = -1;
	while (++i < COLOR_COUNT)
		free(colors[i]);
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
}

int main(int size, char **args)
{
	t_scene	*const scene = &(t_scene){0};
	
	if (size == 2)
	{
		if (!parser(args[1], scene))
			return (clean_all(scene), EXIT_FAILURE);
		scene->player.direction.x = -1;
		scene->player.plane.y = 0.66;
		init_display(scene);
		clean_all(scene);
	}	
	else
		return (panic("Usage", ERR_USAGE, EXIT_FAILURE));
	return (EXIT_SUCCESS);
}