/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tugcekul <tugcekul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:16:39 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/09 07:17:13 by tugcekul         ###   ########.fr       */
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

// void	print_map(t_map *map)
// {
// 	for (int i = 0; i < map->height; i++)
// 	{
// 		printf("%s\n", map->layout[i]);	
// 	}
// }

int	close_window(t_scene *scene)
{
	clean_all(scene);
	exit(EXIT_SUCCESS);
}

void init_scene(t_mlx *mlx)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, mlx->win_width,mlx->wid_height, "Cub3D");
	mlx->img = mlx_new_image(mlx->mlx, mlx->win_width, mlx->wid_height);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->size_line, &(int){0});
}

void find_player_position(t_scene *scene)
{
	int		i;
	int		j;

	i = -1;
	while (++i < scene->map.height)
	{
		j = -1;
		while (++j < scene->map.width)
		{
			if (ft_strchr(MAP_LAYOUT_CHARS, scene->map.layout[i][j]))
			{
				if (ft_strchr("NSWE", scene->map.layout[i][j]))
				{
					scene->player.position.x = j + 0.5;
					scene->player.position.y = i + 0.5;
					scene->player.position.z = 0;
					if (scene->player.position.z)
						parser_panic(1, i, "Player", "Player position must be on the ground");
				}
			}
			else
				parser_panic(1, i, "Map", "Invalid char in map layout");
		}
	}
}

void fill_tile(t_mlx *mlx, int x, int y, char type)
{
	int i;
	int j;
	unsigned int *addr = (unsigned int *)mlx->addr;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			int pos = ((((y * TILE_SIZE) + j) * mlx->size_line) + (((x * TILE_SIZE) + i) * (mlx->bits_per_pixel / 8))) / 4;
			if (type == WALL_CHAR)
				addr[pos]= 0xFF0000;
			else if (type == FLOOR_CHAR)
				addr[pos] = 0xFFFFFF;
			else if (type == PLAYER_CHAR)
				addr[pos] = 0xFF0000;
			else if (type == OUTSIDE_CHAR)
				addr[pos] = 0x0000FF;
			else if (type == 'H')
				addr[pos] = 0x00FF00;		
			j++;
		}
		i++;
	}
}

void draw_line(t_mlx *mlx, int x0, int y0, int x1, int y1, int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1)
    {
        // Pikseli çiz
        if (x0 >= 0 && x0 < mlx->win_width && y0 >= 0 && y0 < mlx->wid_height)
        {
            int pos = (y0 * mlx->size_line + x0 * (mlx->bits_per_pixel / 8)) / 4;
            unsigned int *addr = (unsigned int *)mlx->addr;
            addr[pos] = color;
        }

        // Bitiş noktasına ulaştıysak döngüden çık
        if (x0 == x1 && y0 == y1)
            break;

        e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

void ft_render_map(t_scene *scene)
{
    int		x;
	int		y;
	char	**map = scene->map.layout;
	
	y = -1;
	while (++y < scene->map.height)
	{
		x = -1;
		while (++x < scene->map.width)
			fill_tile(&scene->mlx, x, y, map[y][x]);
	}
	t_player *player = &scene->player;
	player->direction.x = 1;
	player->direction.y = -1;
	double planeX = -player->direction.y * 0.66;
	double planeY = player->direction.x * 0.66;

    for (int screenX = 0; screenX < scene->mlx.win_width; screenX++)
    {
        double cameraX = 2 * screenX / (double)scene->mlx.win_width - 1; // X-coordinate in camera space
        double rayDirX = player->direction.x + planeX * cameraX;
        double rayDirY = player->direction.y + planeY * cameraX;
		printf("RayDirX: %f, RayDirY: %f\n", rayDirX, rayDirY);

        int mapX = (int)player->position.x;
        int mapY = (int)player->position.y;

        double sideDistX, sideDistY;
        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

        int stepX, stepY;
        int hit = 0; // Was there a wall hit?

        // Calculate step and initial sideDist
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (player->position.x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - player->position.x) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (player->position.y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - player->position.y) * deltaDistY;
        }

        // Perform DDA
        while (hit == 0)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
            }
			draw_line(&scene->mlx, (int)player->position.x*TILE_SIZE, (int)player->position.y*TILE_SIZE, mapX * TILE_SIZE, mapY * TILE_SIZE, 0x000000);

			if (scene->map.layout[mapY][mapX] == '1') // Wall hit
			{
				hit = 1;
				printf("Hit at %d, %d\n", mapX, mapY);
				fill_tile(&scene->mlx, mapX, mapY, 'H');
				mlx_put_image_to_window(scene->mlx.mlx, scene->mlx.win, scene->mlx.img, 0, 0);

			}
        }
	}
}

int main(int size, char **args)
{
	t_scene	*const scene = &(t_scene){0};
	printf("scene %p\n", scene);
	if (size == 2)
	{
		if (!parser(args[1], scene))
			return (clean_all(scene), EXIT_FAILURE);
		find_player_position(scene);
		init_scene(&scene->mlx);
		ft_render_map(scene);
		mlx_put_image_to_window(scene->mlx.mlx, scene->mlx.win, scene->mlx.img, 0, 0);
		mlx_hook(scene->mlx.win, 17, 0, close_window, scene);
		mlx_loop(scene->mlx.mlx);
	}	
	else
		return (panic("Usage", ERR_USAGE, EXIT_FAILURE));
	return (EXIT_SUCCESS);
}