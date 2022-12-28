#ifndef MINIRT_H
# define MINIRT_H

# include "vector_utils.h"
# include "libft.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <stdio.h>
# include <float.h>
# define SHININESS 8.0

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;

typedef struct s_ray
{
	t_vec	start;
	t_vec	direction;
}	t_ray;

typedef struct s_sphere
{
	t_vec	center;
	double	radius;
}	t_sphere;

typedef struct s_plane
{
	t_vec	normal;
	t_vec	pos;
}	t_plane;

typedef struct s_cylinder	t_cylinder;
struct s_cylinder
{
	t_vec	normal;
	t_vec	pos;
	double	radius;
	double	height;
};

typedef struct s_material
{
	t_color	diffuse_ref;
	t_color	specular_ref;
	double	shininess;
}	t_material;

typedef enum e_shape_type
{
	ST_SPHERE,
	ST_PLANE,
	ST_CYLINDER,
	ST_NONE
}	t_shape_type;

typedef struct s_intersection
{
	double	distance;
	t_vec	pos;
	t_vec	normal;
}	t_intersection;

typedef struct s_shape		t_shape;
struct s_shape
{
	t_shape_type	type;
	t_sphere		sphere;
	t_plane			plane;
	t_cylinder		cylinder;
	t_material		material;
	t_shape			*next;
} ;

typedef struct s_nearest
{
	t_intersection	i_point;
	t_shape			shape;
	bool			flag;
}	t_nearest;

typedef enum e_light_type
{
	POINT,
	DIRECTIONAL
}	t_light_type;

typedef struct s_light
{
	t_light_type	type;
	t_vec			vec;
	t_color			illuminance;
	double			brightness_ratio; // ?????????????
}	t_light;

typedef struct s_ambient
{
	t_color	ambient_illuminance;
	t_color	ambient_ref;
}	t_ambient;

typedef struct s_camera
{
	t_vec	pos;
	double	fov;
	t_vec	orientation;
}	t_camera;

typedef struct s_config
{
	t_shape		*shape_list;
	t_material	*material;
	size_t		num_shapes;
	t_light		light;
	t_ambient	ambient;
	t_camera	camera;
}	t_config;

typedef struct s_quadratic	t_quadratic;
struct s_quadratic
{
	double	a;
	double	b;
	double	c;
	double	d;
	double	sol1;
	double	sol2;
	double	sol;
} ;

/* --------------------------------
config {
	t_shape *shape_list;
	size_t	num_shapes;
	t_light	light;
	t_color	ambient_illuminance;
}

---------------------------------- */

t_config	init_config(char **argv);
void		ray_trace(t_config config);
void		draw(t_color color);
t_color		trace(t_config config, t_ray ray);
t_color		get_luminance(t_config config, t_nearest nearest, t_ray ray);
t_nearest	get_shadow_ray(t_config config, t_nearest nearest, \
		t_vec light_dir);
t_color		add_specular_luminance(t_nearest nearest, t_color illuminance, \
		t_vec light_dir, t_ray camera_ray);
t_color		add_diffuse_luminance(t_shape shape, t_color illuminance, \
		double normal_light_dir_dot);
t_color		add_ambient_luminance(t_config config);
t_color		add_color(t_color n, t_color m);
t_nearest	get_nearest(t_config config, t_ray ray, double max_d, bool shadow);
bool		is_hittable(t_shape shape, t_ray ray, t_intersection *i_point);
bool		is_hittable_plane(t_plane pln, t_ray ray, t_intersection *i_point);
bool		is_hittable_sphere(t_sphere sph, t_ray ray, \
		t_intersection *i_point);
double		get_solution_of_quadratic_equation(t_sphere sph, t_ray ray, \
		double d);
double		discriminant(t_sphere sph, t_ray ray);
t_ray		get_camera_ray(double x, double y, t_camera camera);
//t_ray	get_camera_ray(size_t x, size_t y, t_camera camera);
//t_ray	get_camera_ray(size_t x, size_t y, t_vec camera_pos);

#endif
