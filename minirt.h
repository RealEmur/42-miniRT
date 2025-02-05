/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:17:01 by emyildir          #+#    #+#             */
/*   Updated: 2025/02/05 17:48:34 by emyildir         ###   ########.fr       */
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

#define ERR_USAGE "./cub3D <a map file>"
#define ERR_EXTENSION "Scene description files must have '.cub' extension"
#define ERR_SCENE_FORMAT "Description file is not valid."

#define ERR_WRONG_FORMAT "Arguement count didn't match."
#define ERR_ARG_FLOAT "Arguement must be in (float) format."
#define ERR_ARG_RGB "Arguement must be in (R,G,B) format."
#define ERR_ARG_COORDINATE "Arguement must be in (x,y,z) format."
#define ERR_ARG_POSITION "Arguement must be in (x,y,z) format."
#define ERR_ARG_INTEGER "Arguement must be in (integer) format." 
#define ERR_RGB_RANGE "RGB values must be between [0-255]."
#define ERR_VECTOR_RANGE "Vector values must be between [-1.0,1.0]"


#define RADIAN(degree) ((degree) * M_PI / 180.0)
#define WIDTH 1920
#define HEIGHT 1080

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
	char	*north_texture;
	char	*east_texture;
	char	*west_texture;
	char	*south_texture;
	t_rgb	floor_color;
	t_rgb	ceiling_color;
} t_options;

typedef struct s_player
{
	t_position	position;
	t_vector	rotation;
}	t_player;

typedef struct s_scene 
{
	
	char		**map;
	t_player	player;
	t_options	options;
}	t_scene;



int panic(char *tag, char *error, int rtrn_val);
void	parser_panic(int line, char *title, char *err);
int	is_float(char *str);
int	is_rgb(char *str);
int	is_valid_extension(char *path);
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


#endif