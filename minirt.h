/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shongou <shongou@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 23:34:10 by shongou           #+#    #+#             */
/*   Updated: 2023/01/04 23:34:12 by shongou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include "vector_utils.h"
# include "libft.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <stdio.h>
# include <float.h>
# include "mlx_int.h"
# include "mlx.h"

# define SHININESS 8.0
# define SPECULAR_REF 0.3
# define __GNU_SOURCE 1

# define EXPOSE 12

# define HEIGHT 600
# define WIDTH 800

# define NO_ERROR 0
# define MLX_INIT_ERR 1
# define NEW_WINDOW_ERR 2
# define NEW_IMAGE_ERR 4

typedef struct s_err		t_err;
struct s_err
{
	int	err_flag;
	int	scene_obj;
} ;

typedef enum e_scene_obj	t_scene_obj;
enum e_scene_obj{
	A = 1,
	C = 2,
	L = 4,
	PL = 8,
	SP = 16,
	CY = 32,
} ;

typedef union s_my_double
{
	unsigned long long	ulnum;
	double				dnum;
}	t_my_double;

typedef struct s_image		t_image;
struct s_image
{
	void	*img_ptr;
	char	*addr;
	int		size_line;
	int		bpp;
	int		endian;
} ;

//typedef struct s_status		t_status;
//struct s_status
//{
//	void		*mlx;
//	void		*mlx_win;
//	t_image		img;
//	t_config	config;
//};

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
	double			brightness_ratio;
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

typedef struct s_status		t_status;
struct s_status
{
	void		*mlx;
	void		*mlx_win;
	t_image		img;
	t_config	config;
};

typedef struct s_quadratic	t_quadratic;
struct s_quadratic
{
	double	a;
	double	b;
	double	c;
	double	sol1;
	double	sol2;
	double	sol;
} ;

typedef enum e_error_type	t_error_type;
enum e_error_type
{
	MALLOC_ERROR = 1,
	IDENTIFIER_ERROR = 2,
	NUMBER_OF_ELEMENT_ERROR = 4,
	NULL_STR = 8,
	INVALID_COLOR = 16,
	INVALID_VECTOR = 32,
	INVALID_ORIENTATION = 64,
	INVALID_FOV = 128,
	INVALID_RATIO = 256,
	INVALID_SIZE = 512,
	INVALID_FILE = 1024,
	OPEN_ERROR = 2048,
};

/* --------------------------------
config {
	t_shape *shape_list;
	size_t	num_shapes;
	t_light	light;
	t_color	ambient_illuminance;
}
---------------------------------- */
// init.c
t_config	init_config(char **argv);

// ray_trace.c
void		ray_trace(t_config config, t_status *status);
//void		ray_trace(t_config config);
t_color		trace(t_config config, t_ray ray);

// draw.c
void		draw(t_color color, int x, int y, t_image img);
//void		draw(t_color color);

// window_utils.c
t_status	*mlx_run(t_config config);
//t_status	*mlx_run(void);
void		init_image(t_status *status);
int			delete_window(t_status *status);
int			key_hook(int key, t_status *status);
int			rendering(t_status *status);
void		free_list(t_config config);

// get_shadow_ray.c
t_nearest	get_shadow_ray(t_config config, t_nearest nearest, \
		t_vec light_dir);

// utils.c
void		print_vector(t_vec vec, char *msg);
void		add_list_last(t_shape **shape_list, t_shape *node);
char		*remove_nl(char *str, t_err *err);
void		free_strs(char **strs);

// atod.c
double		atod(char *str);
// luminance.c
t_color		add_specular_luminance(t_nearest nearest, t_light light, \
		t_vec light_dir, t_ray camera_ray);
t_color		add_diffuse_luminance(t_shape shape, t_light light, \
		double normal_light_dir_dot);
t_color		add_ambient_luminance(t_config config);
t_color		get_luminance(t_config config, t_nearest nearest, t_ray ray);

// color_utils.c
t_color		add_color(t_color n, t_color m);
t_color		set_color(char *rgb, int *err_flag);
//t_color		set_color(char *rgb);

// get_nearest.c
t_nearest	get_nearest(t_config config, t_ray ray, double max_d, bool shadow);

// is_hittable.c
bool		get_intersection(t_cylinder cyl, t_ray ray, t_quadratic quad, \
		t_intersection *i_point);
bool		is_hittable(t_shape shape, t_ray ray, t_intersection *i_point);
bool		is_hittable_plane(t_plane pln, t_ray ray, t_intersection *i_point);
bool		is_hittable_sphere(t_sphere sph, t_ray ray, \
		t_intersection *i_point);
bool		is_hittable_cylinder(t_cylinder cyl, t_ray ray, \
		t_intersection *i_point);

// equation.c
double		get_solution_of_quadratic_equation(t_sphere sph, t_ray ray, \
		double d);
double		discriminant(t_sphere sph, t_ray ray);
double		cy_get_solution_of_quadratic_equation(double d, t_quadratic *quad);
double		cy_discriminant(t_cylinder cyl, t_ray ray, t_quadratic *quad);

// camera_ray.c
t_ray		get_camera_ray(double x, double y, t_camera camera);
void		get_basis_vector(t_vec *esx, t_vec *esy, t_vec cam_dir);

// set_scene.c
void		set_ambient(char **strs, t_config *config, int *err_flag, \
		int *scene_obj);
void		set_light(char **strs, t_config *config, int *err_flag, \
		int *scene_obj);
void		set_camera(char **strs, t_config *config, int *err_flag, \
		int *scene_obj);

// set_shapes.c
void		set_sphere(char **strs, t_config *config, int *err_flag, \
		int *scene_obj);
void		set_cylinder(char **strs, t_config *config, int *err_flag, \
		int *scene_obj);
void		set_plane(char **strs, t_config *config, int *err_flag, \
		int *scene_obj);
//void	set_sphere(char **split_line, t_shape **shape_list, int *err_flag);
//void	set_cylinder(char **split_line, t_shape **shape_list, int *err_flag);
//void	set_plane(char **split_line, t_shape **shape_list, int *err_flag);

//set_utils.c
t_vec		set_orientation(char *str, int *err_flag);
t_vec		set_coordinates(char *str, int *err_flag);
t_color		set_rgb(char *str, int *err_flag);

//set_utils2.c
double		set_size(char *str, int *err_flag);
double		set_ratio(char *str, int *err_flag);
double		set_fov(char *str, int *err_flag);

//valid_utils.c
bool		valid_color(char *str);
bool		valid_digit(char *str);
bool		valid_vector(char *str);
bool		valid_float(char *str);

//error.c
void		check_obj(int scene_objs);
void		before_set_config_err_handler(int err_flag);
void		error_handler(int fd, char *line, size_t line_n, int error_flag);

//mlx_error.c
void		print_mlx_error(int flag);
void		mlx_error(t_status *status, t_config config, int flag);

#endif
