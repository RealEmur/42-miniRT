/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkul <tkul@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 07:40:44 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/17 19:33:51 by tkul             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	close_window(t_scene *scene)
{
	clean_all(scene);
	exit(EXIT_SUCCESS);
	return (true);
}

int	init_mlx(t_mlx *mlx)
{
	t_image *const	image = &mlx->image;

	mlx->mlx = mlx_init();
	if (!mlx->mlx)
		return (panic("MiniLibX", ERR_MLX_INITIALIZE, false));
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Cub3D");
	if (!mlx->win)
		return (panic("MiniLibX", ERR_WINDOW_INITIALILZE, false));
	image->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	if (!image->img)
		return (panic("MiniLibX", ERR_IMAGE_INITIALILZE, false));
	image->addr = mlx_get_data_addr(image->img, &image->bpp, \
	&image->size_line, &image->endian);
	return (true);
}

int	init_textures(void *mlx, t_texture *textures)
{
	t_texture	*texture;
	t_image		*image;
	int			i;

	i = -1;
	while (++i < TEXTURE_COUNT)
	{
		texture = &textures[i];
		image = &texture->image;
		image->img = mlx_xpm_file_to_image(mlx, \
		texture->path, &texture->width, &texture->height);
		if (!image->img)
			return (panic(texture->path, ERR_XPM_LOAD, false));
		image->addr = mlx_get_data_addr(image->img, &image->bpp, \
		&image->size_line, &image->endian);
	}
	return (true);
}

int	update(void *param)
{
	t_scene *const		scene = param;
	t_timestamp const	current = get_timestamp();
	const double		delta_time = (current - scene->last_tick) / 1000.0;

	scene->last_tick = current;
	player_movement(scene, &scene->player, delta_time);
	render(scene);
	return (1);
}

int	init_display(t_scene *scene)
{
	t_mlx *const	mlx = &scene->mlx;

	if (!init_mlx(&scene->mlx)
		|| !init_textures(mlx->mlx, scene->options.textures))
		return (false);
	mlx_hook(mlx->win, 2, (1L << 0), on_key_press, &scene->pressed_keys);
	mlx_hook(mlx->win, 3, (1L << 1), on_key_release, &scene->pressed_keys);
	mlx_hook(mlx->win, 17, 0, close_window, scene);
	mlx_loop_hook(mlx->mlx, update, scene);
	mlx_loop(mlx->mlx);
	return (true);
}
