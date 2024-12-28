/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emyildir <emyildir@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:17:01 by emyildir          #+#    #+#             */
/*   Updated: 2024/12/28 18:40:00 by emyildir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>

#include "lib/libft/libft.h"
#include "lib/gnl/get_next_line.h"

#define ERR_USAGE "./miniRT <a scene file>"
#define ERR_EXTENSION "Scene description files must have '.rt' extension"
#define ERR_SCENE_FORMAT "Description file is not valid."

typedef enum e_object_types
{
	OBJECT_NONE,
	AMBIENT_LIGHTNING,
	CAMERA,
	LIGHT,
	SPHERE,
	PLANE,
	CYLINDER
}	t_object_types;

typedef struct s_rgb
{
	int		red;
	int		green;
	int		blue;
}	t_rgb;

typedef struct s_coords
{
	float	x;
	float	y;
	float	z;
}	t_coords;

typedef t_coords t_position;
typedef t_coords t_vector;

typedef struct s_object
{
	t_object_types	type;
}	t_object;

typedef struct s_ambient 
{
	t_object_types	type;
	float			light_ratio;
	t_rgb			color;
}	t_ambient;

typedef struct s_camera
{
	t_object_types	type;
	int				fov;
	t_position		position;
	t_vector		vector;
}	t_camera;

typedef struct s_light
{
	t_object_types	type;
	float			light_ratio;
	t_rgb			color;
	t_position		position;
}	t_light;

typedef struct s_sphere
{
	t_object_types	type;
	float			diameter;
	t_rgb			color;
	t_position		position;
}	t_sphere;

typedef struct s_plane
{
	t_object_types	type;
	float			diameter;
	float			height;
	t_rgb			color;
	t_position		position;
}	t_plane;

int panic(char *tag, char *error, int rtrn_val);
int	is_float(char *str);
int	is_rgb(char *str);
int	is_valid_extension(char *path);
int	str_arr_size(char **strs);
void free_str_arr(char **strs);
t_list *parser(char *path);
float strtofloat(char *str);
t_coords	strtocoords(char *str);
int		is_coord(char *str);
int		is_num(char *str);
t_rgb	strtorgb(char *str);
t_object	*parse_ambient_lightning(char **props);
t_object	*parse_camera(char **props);

#endif