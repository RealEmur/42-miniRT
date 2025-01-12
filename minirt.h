/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tugcekul <tugcekul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:17:01 by emyildir          #+#    #+#             */
/*   Updated: 2025/01/11 14:32:21 by tugcekul         ###   ########.fr       */
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

#define ERR_USAGE "./miniRT <a scene file>"
#define ERR_EXTENSION "Scene description files must have '.rt' extension"
#define ERR_SCENE_FORMAT "Description file is not valid."

#define ERR_WRONG_FORMAT "Arguement count didn't match."
#define ERR_ARG_FLOAT "Arguement must be in (float) format."
#define ERR_ARG_RGB "Arguement must be in (R,G,B) format."
#define ERR_ARG_COORDINATE "Arguement must be in (x,y,z) format."
#define ERR_ARG_POSITION "Arguement must be in (x,y,z) format."
#define ERR_ARG_INTEGER "Arguement must be in (integer) format." 
#define ERR_RGB_RANGE "RGB values must be between [0-255]."
#define ERR_VECTOR_RANGE "Vector values must be between [-1.0,1.0]"

# define BLACK		(t_color){0, 0, 0, 0}

#define M_PI 3.14159265358979323846

#define RADIAN(degree) ((degree) * M_PI / 180.0)
#define WIDTH 1920
#define HEIGHT 1080

typedef enum e_render_modes
{
	NOTHING,
	RERENDER_REQUIRED
}	t_render_modes;

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
	double	x;
	double	y;
	double	z;
}	t_coords;

typedef t_coords t_position;
typedef t_coords t_vector;
typedef struct s_viewport
{
	float	width;
	float	height;
}	t_viewport;

typedef struct s_scene 
{
	void	*mlx;
	void	*mlx_win;
	void *canvas;
	t_render_modes render_mode;
	t_list			*objects;
	t_list			*triangles;
	t_viewport		viewport;
}	t_scene;


typedef struct s_object
{
	t_object_types	type;
}	t_object;

typedef struct s_ambient 
{
	t_object_types	type;
	float			brightness;
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
	float			brightness;
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
	t_rgb			color;
	t_vector		vector;
	t_position		position;
}	t_plane;

typedef struct s_cylinder
{
	t_object_types	type;
	t_position		position;
	t_vector		vector;
	float			diameter;
	float			height;
	t_rgb			color;
}	t_cylinder;

typedef struct s_color {
	int t;
	int r;
	int g;
	int b;
}	t_color;

typedef struct s_ray
{
	t_vector	origin;
	t_vector	direction;
}	t_ray;

typedef struct s_triangle {
    t_vector	p1;
    t_vector	p2;
    t_vector	p3;
	t_object	*object;
} t_triangle;

typedef struct s_hit
{
	t_object  *object;
	t_ray		ray;
	t_vector	point;
	t_vector	normal;
	t_color	color;
	double t;
	t_triangle *triangles;
}	t_hit;


int panic(char *tag, char *error, int rtrn_val);
void	parser_panic(int line, char *title, char *err);
int	is_float(char *str);
int	is_rgb(char *str);
int	is_valid_extension(char *path);
int	str_arr_size(char **strs);
void free_str_arr(char **strs);
t_list *parser(char *path);
float strtofloat(char *str);
t_coords	strtocoord(char *str);
int		is_coord(char *str);
int		is_num(char *str);
t_rgb	strtorgb(char *str);
t_object	*parse_ambient(char **props, int line);
t_object	*parse_camera(char **props, int line);
t_object	*parse_light(char **props, int line);
t_object	*parse_sphere(char **props, int line);
t_object	*parse_plane(char **props, int line);
t_object	*parse_cylinder(char **props, int line);
int			validator(t_list	*objlist);
int			validate_vector(t_vector vector);
int	validate_rgb(t_rgb rgb);
void    init_mlx(t_scene *scene);
int display_scene(t_scene *scene);
void	print_objects(t_list *objlist);
t_vector sphere_point(t_vector center, double radius, double theta, double phi);
void triangulate_sphere(t_list **triangles, t_object *object, t_vector center, double radius, int slices, int stacks);
t_vector Vector_normalize(t_vector v);
void    triangulate_plane(t_list **triangles, t_object *object,t_vector origin,int subdivisions);
void    triangulate_cylinder(t_list **triangles, t_object *object, t_vector base, double radius, double height, int slices, int stack);

#endif