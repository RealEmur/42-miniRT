/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:16:39 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/12 16:36:33 by emyildir         ###   ########.fr       */
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
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Cub3D");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
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
					scene->map.layout[i][j] = '0';
					if (scene->player.position.z)
						parser_panic(1, i, "Player", "Player position must be on the ground");
				}
			}
			else
				parser_panic(1, i, "Map", "Invalid char in map layout");
		}
	}
}

void draw_line(t_mlx *mlx, int x0, int y0, int x1, int y1, unsigned int color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1)
    {
        draw_pixel(mlx, x0, y0, color);
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

void draw_pixel(t_mlx *mlx, int x, int y, unsigned int color)
{
	unsigned int	*addr = (unsigned int *)mlx->addr;
	const int		pos = (y * mlx->size_line + x * (mlx->bits_per_pixel / 8)) / 4;
	
	addr[pos]= color;
}

void ft_render_map(t_scene *scene)
{
	t_player *player = &scene->player;
	char	**const map = scene->map.layout;
	double	planeX = player->plane.x;
	double	planeY = player->plane.y;
	int		x;
	int		y;

	x = -1;
	while (++x < WIDTH)
	{
		y = -1;
		while (++y < HEIGHT)
		{
			if (y < HEIGHT / 2)
				draw_pixel(&scene->mlx, x, y, rgbtouint(*scene->options.colors[CEILING_COLOR]));
			else 
				draw_pixel(&scene->mlx, x, y, rgbtouint(*scene->options.colors[FLOOR_COLOR]));
		}	
	}

    for (int screenX = 0; screenX < WIDTH; screenX++)
    { 
        double cameraX = 2 * screenX / (double)WIDTH - 1;
        double rayDirX = player->direction.x + planeX * cameraX;
        double rayDirY = player->direction.y + planeY * cameraX; 

        int mapX = (int)player->position.x;
        int mapY = (int)player->position.y;

        double sideDistX, sideDistY;
        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

        int stepX, stepY;
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
		int side;
        while (1)
        {
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
				side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
				side = 1;
                mapY += stepY;
            }
			if (map[mapY][mapX] == '1') 
			{	
				double	perpWallDist;
				if(side == 0) 
					perpWallDist = (sideDistX - deltaDistX);
      			else 
				    perpWallDist = (sideDistY - deltaDistY);

				 int lineHeight = (int)(HEIGHT / perpWallDist);

				int drawStart = -lineHeight / 2 + HEIGHT / 2;
				if (drawStart < 0)
					drawStart = 0;
				int drawEnd = lineHeight / 2 + HEIGHT / 2;
				if (drawEnd >= HEIGHT)
					drawEnd = HEIGHT - 1;
				if (side == 1)
					draw_line(&scene->mlx, screenX, drawStart, screenX, drawEnd, 0xFFFF00);
				else 
					draw_line(&scene->mlx, screenX, drawStart, screenX, drawEnd, 0xFFDD00);
				break;
			}
        }
	}
}

int	on_key_press(int keycode, void *param)
{
	t_scene	*const scene = param;
	char **map = scene->map.layout;
	double *posX = &(scene->player.position.x);
	double *posY = &(scene->player.position.y);
	double *dirX = &(scene->player.direction.x);
	double *dirY = &(scene->player.direction.y);
	double	*planeX = &(scene->player.plane.x);
	double	*planeY = &(scene->player.plane.y);
	if (keycode == KEY_W)
	{

		if(map[(int)(*posY + *dirY)][(int)*posX] == '0') *posY += *dirY;
    	if(map[(int)(*posY)][(int)(*posX + *dirX)] == '0') *posX += *dirX;
		printf("sa\n");
	}
	else if (keycode == KEY_A) // SOLA DÖNÜŞ
	{
		double angle = 10 * M_PI / 180.0;  // 10 derece dönüş
		double cosA = cos(angle);
		double sinA = sin(angle);

		double oldDirX = *dirX;
		double oldPlaneX = *planeX;

		*dirX = oldDirX * cosA - *dirY * sinA;
		*dirY = oldDirX * sinA + *dirY * cosA;
		*planeX = oldPlaneX * cosA - *planeY * sinA;
		*planeY = oldPlaneX * sinA + *planeY * cosA;
	}
	if (keycode == KEY_S)
	{
		if(map[(int)(*posY - *dirY)][(int)(*posX)] == '0') *posY -= *dirY;
    	if(map[(int)(*posY)][(int)(*posX - *dirX)] == '0') *posX -= *dirX;
	}
	else if (keycode == KEY_D) // SAĞA DÖNÜŞ
	{
		double angle = -10 * M_PI / 180.0;  // -10 derece sağa dönüş
		double cosA = cos(angle);
		double sinA = sin(angle);

		double oldDirX = *dirX;
		double oldPlaneX = *planeX;

		*dirX = oldDirX * cosA - *dirY * sinA;
		*dirY = oldDirX * sinA + *dirY * cosA;
		*planeX = oldPlaneX * cosA - *planeY * sinA;
		*planeY = oldPlaneX * sinA + *planeY * cosA;
	}
	ft_render_map(scene);
	mlx_put_image_to_window(scene->mlx.mlx, scene->mlx.win, scene->mlx.img, 0, 0);
	return 1;
}

int main(int size, char **args)
{
	t_scene	*const scene = &(t_scene){0};
	scene->player.direction.x = -1;
	scene->player.direction.y = 0;
	scene->player.plane.x = 0;
	scene->player.plane.y = .66;
	if (size == 2)
	{
		if (!parser(args[1], scene))
			return (clean_all(scene), EXIT_FAILURE);
		find_player_position(scene);
		init_scene(&scene->mlx);
		ft_render_map(scene);
		mlx_put_image_to_window(scene->mlx.mlx, scene->mlx.win, scene->mlx.img, 0, 0);
		mlx_key_hook(scene->mlx.win, on_key_press, scene);
		mlx_hook(scene->mlx.win, 17, 0, close_window, scene);
		mlx_loop(scene->mlx.mlx);
	}	
	else
		return (panic("Usage", ERR_USAGE, EXIT_FAILURE));
	return (EXIT_SUCCESS);
}