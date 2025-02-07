/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:17:01 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/07 04:30:51 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

#include "lib/libft/libft.h"
#include "lib/gnl/get_next_line.h"
#include "lib/mlx/mlx.h"

#define MAP_FILE_EXTENSION ".cub"
#define MAP_MAPLAYOUT_CHARS " 01WNSE"

#define ERR_USAGE "./cub3D <a map file>"
#define ERR_EXTENSION "Map description files must have '.cub' extension"
#define ERR_FILE_FORMAT "Description file is not valid."

#define ERR_WRONG_FORMAT "Arguement count didn't match."
#define ERR_ARG_FLOAT "Arguement must be in (float) format."
#define ERR_ARG_XPM "Arguement must be a xpm file path."
#define ERR_ARG_RGB "Arguement must be in (R,G,B) format."
#define ERR_ARG_COORDINATE "Arguement must be in (x,y,z) format."
#define ERR_ARG_POSITION "Arguement must be in (x,y,z) format."
#define ERR_ARG_INTEGER "Arguement must be in (integer) format." 
#define ERR_RGB_RANGE "RGB values must be between [0-255]."
#define ERR_VECTOR_RANGE "Vector values must be between [-1.0,1.0]"
#define ERR_SPACE_SEP "Elements can not be seperated by space only lines"
#define ERR_MAP_NOTLAST "Map content must be last thing in the map file"
#define ERR_INVALID_INDETIFIER "Identifier is not valid"

#define TEXTURE_COUNT 4
#define NORTH_TEXTURE 0
#define EAST_TEXTURE 1
#define SOUTH_TEXTURE 2
#define WEST_TEXTURE 3

#define COLOR_COUNT 2
#define CEILING_COLOR 0
#define FLOOR_COLOR 1

#define RADIAN(degree) ((degree) * M_PI / 180.0)
#define WIDTH 1920
#define HEIGHT 1080

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

typedef struct t_coords
{
	double	x;
	double	y;
	double	z;
}	t_coords;

typedef t_coords t_position;
typedef t_coords t_vector;

typedef	struct	s_options
{
	char	*textures[TEXTURE_COUNT];
	t_rgb	colors[COLOR_COUNT];
} t_options;

typedef struct s_player
{
	t_position	position;
	t_vector	rotation;
}	t_player;

typedef struct s_map
{
	int		width;
	int		height;
	char	**layout;
}	t_map;

typedef struct s_scene 
{
	t_map		map;
	t_player	player;
	t_options	options;
}	t_scene;



int panic(char *tag, char *error, int rtrn_val);
void	parser_panic(int line, char *title, char *err);
int	is_float(char *str);
int	is_rgb(char *str);
int	validate_extension(char *path, char *extension);
int	str_arr_size(char **strs);
void free_str_arr(char **strs);
int	 parser(char *path, t_scene *scene);
float strtofloat(char *str);
t_coords	strtocoord(char *str);
int		is_coord(char *str);
int		is_num(char *str);
t_rgb	strtorgb(char *str);
int			validator(t_list	*objlist);
int			validate_vector(t_vector vector);
int	validate_rgb(t_rgb rgb);
int	parse_texture(t_scene *scene, char **props, int type, int line);
int	parse_color(t_scene *scene, char **props, int type, int line);
int parse_map(t_scene *scene, int fd, char *line, int *line_count);
int	str_append(char **s1, char *s2);
char    **load_map(int fd, char *firstline, int *line_count);
int		get_map_width(char **map);
int		extend_map(char **map, int width);


#endif