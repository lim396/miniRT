#ifndef MINIRT_H
#define MINIRT_H

#include "vector_utils.h"
#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <stdio.h>
#define SHINESS 8.0

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
} t_color;

typedef struct s_ray
{
	t_vec	start;
	t_vec	direction;
} t_ray;

typedef struct s_sphere
{
	t_vec	center;
	double	radius;
} t_sphere;

typedef struct s_plane
{
	t_vec	normal;
	t_vec	pos;
} t_plane;

typedef struct s_material
{
	//t_color	ambient_ref;
	t_color	diffuse_ref;
	t_color	specular_ref;
	double	shininess;
} t_material;

typedef enum e_shape_type
{
	ST_SPHERE,
	ST_PLANE,
	ST_NONE
} t_shape_type;

typedef struct s_intersection
{
	double	distance;
	t_vec	pos;
	t_vec	normal;
} t_intersection;

typedef struct s_shape
{
	t_shape_type	type;
	//union
	//{
	t_sphere		sphere;
	t_plane			plane;
//	t_intersection	i_point;
	t_material		material;
	//add t_intersection var in t_shape or t_sphere,t_plane?
	//}
} t_shape;

typedef struct	s_nearest
{
	t_intersection	i_point;
	t_shape			shape;
	bool			flag;
} t_nearest;

typedef enum e_light_type
{
	POINT,
	DIRECTIONAL
} t_light_type;

typedef struct s_light
{
	t_light_type	type;
	t_vec			vec;
	t_color			illuminace;
	double	brightness_ratio; // ?????????????
} t_light;

typedef struct s_ambient
{
	t_color	ambient_illuminance;
	t_color	ambient_ref;
} t_ambient;

typedef struct s_camera
{
	t_vec	pos;
	int		fov;
	t_vec	orientation;
} t_camera;

typedef struct s_config
{
	t_shape		*shape_list; //change from array to list?
	t_material	*material;
	size_t		num_shapes;
	t_light		light;
	t_ambient	ambient;
	t_camera	camera;
} t_config;


/* --------------------------------
config {
	t_shape *shape_list;
	size_t	num_shapes;
	t_light	light;
	t_color	ambient_illuminance;
}

---------------------------------- */
#endif
