/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:16:39 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/14 11:37:12 by emyildir         ###   ########.fr       */
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

/* int	close_window(t_scene *scene)
{
	clean_all(scene);
	exit(EXIT_SUCCESS);
}

void init_scene(t_mlx *mlx, t_scene *scene)
{
	int i;
	int	trash;
	i = -1;
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIDTH, HEIGHT, "Cub3D");
	mlx->img = mlx_new_image(mlx->mlx, WIDTH, HEIGHT);
	mlx->addr = mlx_get_data_addr(mlx->img, &mlx->bits_per_pixel, &mlx->size_line, &(int){0});
	while (++i < TEXTURE_COUNT)
	{
		scene->options.textures[i].img = mlx_xpm_file_to_image(mlx->mlx, scene->options.textures[i].path, &scene->options.textures[i].width, &scene->options.textures[i].height);
		scene->options.textures[i].addr = mlx_get_data_addr(scene->options.textures[i].img, &scene->options.textures[i].bits_per_pixel, &scene->options.textures[i].size_line, &trash);
		if (!scene->options.textures[i].img || !scene->options.textures[i].addr)
			panic("Texture", "Couldn't load texture", EXIT_FAILURE);
	}
}

void draw_pixel(t_mlx *mlx, int x, int y, unsigned int color)
{
	unsigned int	*addr = (unsigned int *)mlx->addr;
	const int		pos = (y * mlx->size_line + x * (mlx->bits_per_pixel / 8)) / 4;
	
	addr[pos]= color;
}

t_texture	*get_texture(t_texture *textures, int side, double ray_x, double ray_y)
{
	if (side == 0 && ray_x > 0)
		return (&textures[0]);
	else if (side == 0 && ray_x < 0)
		return (&textures[1]);
	else if (side == 1 && ray_y > 0)
		return (&textures[2]);
	else
		return (&textures[3]);
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

				double wallX; 
				if (side == 0)
					wallX = player->position.y + perpWallDist * rayDirY;
				else
					wallX = player->position.x + perpWallDist * rayDirX;
				wallX -= floor((wallX));
				
				t_texture *texture = get_texture(scene->options.textures, side, rayDirX, rayDirY);
				int texX = (int)(wallX * (double)(texture->width));
				if (side == 0 && rayDirX > 0) 
					texX = texture->width - texX - 1;
				if (side == 1 && rayDirY < 0) 
					texX = texture->width - texX - 1;

				double step = (double)texture->height / lineHeight;
				double texPos = (drawStart - (HEIGHT / 2) + (lineHeight / 2)) * step;
				for (int y = drawStart; y < drawEnd; y++)
				{
					int texY = (int)texPos & (texture->height - 1);
					texPos += step;
					unsigned int index = y * WIDTH + screenX;
					((unsigned int *)scene->mlx.addr)[index] = ((unsigned int *)texture->addr)[texture->width * texY + texX];
				}

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
		//printf("FPS: %d\n", (int)(1.0 / delta_time));
	}
	return (1);
}
 */
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