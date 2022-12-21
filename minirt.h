#ifdef MINIRT_H
#define MINIRT_H

#include "vector_utils.h"
#include <stdio.h>

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
	t_color	ambient_ref;
	t_color	diffuse_ref;
	t_color	specular_ref;
	double	shininess;
} t_material;

typedef enum e_shape_type
{
	ST_SPHERE,
	ST_PLANE
} ;

typedef struct s_shape
{
	e_shape_type	type;
	//union
	//{
	t_sphere		sphere;
	t_plane			plane;
	//}
} t_shape;

typedef enum e_light_type
{
	POINT,
	DIRECTIONAL
} ;

typedef struct s_light
{
	e_light_type	type;
	t_vec			vec;
	t_color			illuminace;
} t_light;

typedef struct s_config
{
	t_shape	*shape_list;
	size_t	num_shapes;
	t_light	light;
	t_color	ambient_illuminance;
} t_config;

typedef struct s_intersection
{
	double	distance;
	t_vec	pos;
	t_vec	normal;
} t_intersection;

#endif
