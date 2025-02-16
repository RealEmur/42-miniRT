/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:17:01 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/14 00:25:49 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <sys/time.h>

#include "lib/libft/libft.h"
#include "lib/gnl/get_next_line.h"
#include "lib/mlx/mlx.h"

#define ERR_USAGE "./cub3D <a map file>"
#define ERR_EXTENSION "Map description files must have '.cub' extension"
#define ERR_FILE_FORMAT "Description file is not valid."
#define ERR_WRONG_FORMAT "Arguement count didn't match."
#define ERR_ARG_XPM "Arguement must be a xpm file path."
#define ERR_ARG_RGB "Arguement must be in (R,G,B) format." 
#define ERR_RGB_RANGE "RGB values must be between [0-255]."
#define ERR_SPACE_SEP "Elements can not be seperated by space"
#define ERR_MAP_NOTLAST "Map content must be last thing in the map file"
#define ERR_INVALID_IDENTIFIER "Identifier is not valid"
#define ERR_MULTIPLE_TEXTURE "Map file contains multiple options for this texture"
#define ERR_MULTIPLE_COLOR "Map file contains multiple color for this scene"
#define ERR_MAP_REQUIRED "Couldn't find map layout in map file"
#define ERR_TEXTURE_MISSING "There are missing textures in map file"
#define ERR_COLOR_MISSING "There are missing colors in map file"
#define ERR_MAP_INVALIDCHAR "Invalid char usage in map"
#define ERR_MAP_PLAYER "There must be 1 player character in map"
#define ERR_DOUBLE_MAP "There are multiple maps in layout"
#define ERR_INVALID_MAP "Map is not valid"
#define ERR_MLX_INITIALIZE "Couldn't initialize mlx"
#define ERR_WINDOW_INITIALILZE "Couldn't initialize window"
#define ERR_IMAGE_INITIALILZE "Couldn't initialize image"
#define ERR_XPM_LOAD "Couldn't load xpm file"

#define MAP_FILE_EXTENSION ".cub"
#define MAP_LAYOUT_CHARS " $01WNSE"

#define TEXTURE_COUNT 4
#define NORTH_TEXTURE 0
#define WEST_TEXTURE 3
#define EAST_TEXTURE 1
#define SOUTH_TEXTURE 2

#define COLOR_COUNT 2
#define CEILING_COLOR 0
#define FLOOR_COLOR 1

#define WIDTH 1280
#define HEIGHT 720

#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_UP 65362
#define KEY_DOWN 65364
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define KEY_ESC 65307

#define WALL_CHAR '1'
#define MOVEABLE_CHARS "0NSWE"

#define PLAYER_RADIUS 0.2
#define	MOVE_SPEED 3.0
#define	ROTATION_SPEED 1

typedef struct timeval	t_timeval;
typedef struct s_coords t_coords;
typedef t_coords t_position;
typedef t_coords t_vector;
typedef unsigned long long t_timestamp;

typedef enum e_directions
{
	NORTH,
	WEST,
	SOUTH,
	EAST
}	t_directions;

typedef enum e_map_key
{
	MAPKEY_NOTHING,
	MAPKEY_INVALID,
	TEXTURE_NORTH,
	TEXTURE_WEST,
	TEXTURE_EAST,
	TEXTURE_SOUTH,
	COLOR_CEILING,
	COLOR_FLOOR,
	MAP_LAYOUT
}	t_map_key;

typedef struct s_rgb
{
	int		red;
	int		green;
	int		blue;
}	t_rgb;

typedef struct s_coords
{
	double	x;
	double	y;
}	t_coords;

typedef struct s_image
{
	int		size_line;
	int		bpp;
	int		endian;
	void	*img;
	char	*addr;
}	t_image;

typedef struct s_texture
{
	char	*path;
	int		width;
	int		height;
	t_image	image;
}	t_texture;

typedef	struct	s_options
{
	t_texture textures[TEXTURE_COUNT];
	t_rgb	*colors[COLOR_COUNT];
} t_options;

typedef struct s_player
{
	t_position		position;
	t_vector		direction;
	t_vector		plane;
	t_directions	initial_direction;
}	t_player;

typedef struct s_map
{
	int		width;
	int		height;
	char	**layout;
}	t_map;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_image	image;
}	t_mlx;

typedef struct s_ray
{
	int			step_x;
	int			step_y;
	int			draw_start;
	int			draw_end;
	int			height;
	int			current_x;
	double		deltadistx;
	double		deltadisty;
	double		sidedistx;
	double		sidedisty;
	t_vector	dir;
} t_ray;

typedef struct s_scene 
{
	t_map		map;
	t_mlx		mlx;
	t_player	player;
	t_options	options;
	t_list		*pressed_keys;
	t_timestamp	last_tick;
}	t_scene;



int		panic(char *tag, char *error, int rtrn_val);
int		is_rgb(char *str);
int		validate_extension(char *path, char *extension);
int		str_arr_size(char **strs);
int		parser(char *path, t_scene *scene);
int		is_num(char *str);
int		validate_rgb(t_rgb rgb);
int		parse_texture(t_scene *scene, char **props, int type, int line);
int		parse_color(t_scene *scene, char **props, int type, int line);
int		parse_map(t_scene *scene, int fd, char *line, int *line_count);
int		str_append(char **s1, char *s2);
int		get_map_width(char **map);
int		extend_map(char **map, int width);
int		is_map_line(char *line);
int		validate_map(char **map);
int		rgbtouint(t_rgb rgb);
int		on_key_press(int keycode, void *param);
int		on_key_release(int keycode, void *param);
int		is_key_pressed(t_list *pressed_keys, int keycode);
int		init_display(t_scene *scene);
void	player_movement(t_scene *scene, t_player *player, double delta_time);
void 	free_str_arr(char **strs);
void	parser_panic(int line, char *title, char *err);
void	render(t_scene *scene);
void 	draw_pixel(t_image	*image, int x, int y, unsigned int color);
void	draw_background(t_image *image, t_rgb	**rgbs);
void 	close_window(t_scene *scene);
void	clean_all(t_scene *scene);
char    **load_map(int fd, char *firstline, int *line_count);
t_rgb	strtorgb(char *str);
t_timestamp	get_timestamp(void);
t_texture	*get_texture(t_texture *textures, int side, double ray_x, double ray_y);
#endif