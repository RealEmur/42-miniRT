/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 19:28:15 by tkul              #+#    #+#             */
/*   Updated: 2025/02/17 19:33:40 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	clean_fd(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		free(line);
	}
}

void	clean_all(t_scene *scene)
{
	int					i;
	t_mlx *const		mlx = &scene->mlx;
	t_texture *const	textures = scene->options.textures;

	if (scene->map.layout)
		free_str_arr(scene->map.layout);
	i = -1;
	while (++i < TEXTURE_COUNT)
	{
		free(textures[i].path);
		if (mlx->mlx && textures[i].image.img)
			mlx_destroy_image(mlx->mlx, textures[i].image.img);
	}
	if (mlx->mlx && mlx->image.img)
		mlx_destroy_image(mlx->mlx, mlx->image.img);
	i = -1;
	while (++i < COLOR_COUNT)
		free(scene->options.colors[i]);
	if (mlx->win)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->mlx)
		mlx_destroy_display(mlx->mlx);
	free(mlx->mlx);
	ft_lstclear(&scene->pressed_keys, free);
}
