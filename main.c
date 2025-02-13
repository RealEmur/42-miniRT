/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:16:39 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/13 21:52:43 by emyildir         ###   ########.fr       */
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

int	move(void *param, double delta_time)
{
	t_scene	*const scene = param;
	t_list	*pressed_keys = scene->pressed_keys;
	
	char **map = scene->map.layout;
	double *posX = &(scene->player.position.x);
	double *posY = &(scene->player.position.y);
	double *dirX = &(scene->player.direction.x);
	double *dirY = &(scene->player.direction.y);
	double	*planeX = &(scene->player.plane.x);
	double	*planeY = &(scene->player.plane.y);
		
	if (is_key_pressed(pressed_keys, KEY_ESC))
		close_window(scene);
	float moveSpeed = 3 * delta_time;

	if (is_key_pressed(pressed_keys, KEY_W)) {
		float newY = *posY + (*dirY * moveSpeed);
		float newX = *posX + (*dirX * moveSpeed);

		if (map[(int)(newY + PLAYER_RADIUS)][(int)(*posX)] == '0' && 
			map[(int)(newY - PLAYER_RADIUS)][(int)(*posX)] == '0') {
			*posY = newY;
		}
		if (map[(int)(*posY)][(int)(newX + PLAYER_RADIUS)] == '0' && 
			map[(int)(*posY)][(int)(newX - PLAYER_RADIUS)] == '0') {
			*posX = newX;
		}
	}

	if (is_key_pressed(pressed_keys, KEY_A)) {
		float newX = *posX - (*dirY * moveSpeed);
		float newY = *posY + (*dirX * moveSpeed);

		if (map[(int)(*posY)][(int)(newX + PLAYER_RADIUS)] == '0' && 
			map[(int)(*posY)][(int)(newX - PLAYER_RADIUS)] == '0') {
			*posX = newX;
		}
		if (map[(int)(newY + PLAYER_RADIUS)][(int)(*posX)] == '0' && 
			map[(int)(newY - PLAYER_RADIUS)][(int)(*posX)] == '0') {
			*posY = newY;
		}
	}

	if (is_key_pressed(pressed_keys, KEY_S)) {
		float newY = *posY - (*dirY * moveSpeed);
		float newX = *posX - (*dirX * moveSpeed);

		if (map[(int)(newY + PLAYER_RADIUS)][(int)(*posX)] == '0' && 
			map[(int)(newY - PLAYER_RADIUS)][(int)(*posX)] == '0') {
			*posY = newY;
		}
		if (map[(int)(*posY)][(int)(newX + PLAYER_RADIUS)] == '0' && 
			map[(int)(*posY)][(int)(newX - PLAYER_RADIUS)] == '0') {
			*posX = newX;
		}
	}

	if (is_key_pressed(pressed_keys, KEY_D)) {
		float newX = *posX + (*dirY * moveSpeed);
		float newY = *posY - (*dirX * moveSpeed);

		if (map[(int)(*posY)][(int)(newX + PLAYER_RADIUS)] == '0' && 
			map[(int)(*posY)][(int)(newX - PLAYER_RADIUS)] == '0') {
			*posX = newX;
		}
		if (map[(int)(newY + PLAYER_RADIUS)][(int)(*posX)] == '0' && 
			map[(int)(newY - PLAYER_RADIUS)][(int)(*posX)] == '0') {
			*posY = newY;
		}
	}
	if (is_key_pressed(pressed_keys, KEY_RIGHT))
	{
		double angle = -180 * M_PI / 180.0 * delta_time;
		double cosA = cos(angle);
		double sinA = sin(angle);

		double oldDirX = *dirX;
		double oldPlaneX = *planeX;

		*dirX = oldDirX * cosA - *dirY * sinA;
		*dirY = oldDirX * sinA + *dirY * cosA;
		*planeX = oldPlaneX * cosA - *planeY * sinA;
		*planeY = oldPlaneX * sinA + *planeY * cosA;
	}
	if (is_key_pressed(pressed_keys, KEY_LEFT))
	{
		double angle = 180 * M_PI / 180.0 * delta_time;
		double cosA = cos(angle);
		double sinA = sin(angle);

		double oldDirX = *dirX;
		double oldPlaneX = *planeX;

		*dirX = oldDirX * cosA - *dirY * sinA;
		*dirY = oldDirX * sinA + *dirY * cosA;
		*planeX = oldPlaneX * cosA - *planeY * sinA;
		*planeY = oldPlaneX * sinA + *planeY * cosA;
	}
	return 1;
}


int	update(void *param)
{
	t_scene *const scene = param;
	t_timestamp	const current = get_timestamp();

	double	delta_time =  (current - scene->last_tick) / 1000.0;
	if (delta_time > 0)
	{
		scene->last_tick = current;
		move(scene, delta_time);
		ft_render_map(scene);
		mlx_put_image_to_window(scene->mlx.mlx, scene->mlx.win, scene->mlx.img, 0, 0);
		printf("FPS: %d\n", (int)(1.0 / delta_time));
	}
	return (1);
}

int main(int size, char **args)
{
	t_scene	*const scene = &(t_scene){0};
	scene->player.direction.x = -1;
	scene->player.direction.y = 0;
	scene->player.plane.x = 0;
	scene->player.plane.y = .66;
	scene->last_tick = get_timestamp();
	if (size == 2)
	{
		if (!parser(args[1], scene))
			return (clean_all(scene), EXIT_FAILURE);
		find_player_position(scene);//yeri değişecek parser da kontrol için bu değerler gerekli
		init_scene(&scene->mlx);
		ft_render_map(scene);
		mlx_put_image_to_window(scene->mlx.mlx, scene->mlx.win, scene->mlx.img, 0, 0);
		mlx_hook(scene->mlx.win,  2, (1L<<0),on_key_press, &scene->pressed_keys);
		mlx_hook(scene->mlx.win, 3, (1L<<1), on_key_release, &scene->pressed_keys);
		mlx_loop_hook(scene->mlx.mlx, update, scene);
		mlx_hook(scene->mlx.win, 17, 0, close_window, scene);
		mlx_loop(scene->mlx.mlx);
	}	
	else
		return (panic("Usage", ERR_USAGE, EXIT_FAILURE));
	return (EXIT_SUCCESS);
}