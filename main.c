#include "minirt.h"

#define HEIGHT 512
#define WIDTH 512


t_ray	get_camera_ray(size_t x, size_t y, t_vec camera_pos)
{
	t_ray	ray;
	t_vec	wp; //world_pos
//	double	wx;
//	double	wy;

	//Screen from the upper left origin to a rectangle of width and height 2.0 at the center origin
	wp.x = (2.0 * x) / (WIDTH - 1) - 1.0;
	wp.y = (-2.0 * y) / (HEIGHT - 1) + 1.0;
	wp.z = 0;
	
	//later change screen_camera_pos to world camera_pos
	ray.start = camera_pos;
	ray.direction.x = wp.x - camera_pos.x;
	ray.direction.x = wp.y - camera_pos.y;
	ray.direction.x = wp.z - camera_pos.z;
	return (ray);
}

double	discriminant(t_sphere sph, t_ray ray)
{
	t_vec	sph_center_to_camera;
	double	a;
	double	b;
	double	c;
	double	d;

	sph_center_to_camera = sub(ray.start - sph.center);
	a = dot(ray.direction, ray.direction);
	b = 2 * dot(ray.direction, sph_center_to_camera);
	c = dot(sph_center_to_camera, sph_center_to_camera) - sph.radius * sph.radius;
	d = (b * b) - 4 * a * c;
	return (d);	
}

double	get_solution_of_quadratic_equation(t_sphere sph, t_ray ray, double d)
{
	t_vec	sph_center_to_camera;
	double	a;
	double	b;
	double	t1;
	double	t2;

	sph_center_to_camera = sub(ray.start - sph.center);
	a = dot(ray.direction, ray.direction);
	b = 2 * dot(ray.direction, sph_center_to_camera);
	if (d == 0)
	{
		return (-b / (2 * a));
	}
	else if (d > 0)
	{
		t1 = (-b + sqrt(d)) / (2 * a);
		t2 = (-b - sqrt(d)) / (2 * a);
		if (t1 > 0 && t1 < t2)
			return (t1);
		if (t2 > 0 && t2 < t1)
			return (t2)
	}
	else
		return (-1.0);
}

bool	is_hittable_sphere(t_sphere sph, t_ray ray, t_intersection *i_point)
{
	double	d;
	double	t;

	d = discriminant(sph, ray);
	t = get_solution_of_quadratic_equation(d);
	if (t > 0)
	{
		i_point->distance = t;
		i_point->pos = add(ray.start, mul(t, ray.direction));
		i_point->normal = normalize(sub(i_point->pos, sph.center));
		return (true);
	}
	return (false);
}

bool	is_hittable_plane(t_plane pln, t_ray ray, t_intersection *i_point)
{
	t_vec	pln_to_ray;
	double	dot_ray_dir_pln_normal;
	double	t;

	pln_to_ray = sub(ray.start, pln.pos);
	dot_ray_dir_pln_normal = dot(ray.direction, pln.normal);
	if (dot_ray_dir_pln_normal != 0)
	{
		t = -dot(pln_to_ray, pln.normal) / dot_ray_dir_pln_normal;
		if (t > 0)
		{
			i_point->distance = t;
			i_point->pos = add(ray.start, mul(t, ray.direction));
			i_point->normal = pln.normal;
		}
		return (true);
	}
	return (false);

}

bool	is_hittable(t_shape shape, t_ray ray, t_intersection *i_point)
{
	if (shape.type == ST_SPHERE)
		return (is_hittable_sphere(shape.sphere, ray, i_point));
	if (shape.type == ST_PLANE)
		return (is_hittable_plane(shape.plane, ray, i_point));
//	if (shape.type == ST_SYLINDER)
//		return (is_hittable_sylinder());
	return (false);
}

//t_shape	get_nearest(t_cofig config, t_ray ray, double max_d, bool shadow)
t_nearest	get_nearest(t_cofig config, t_ray ray, double max_d, bool shadow)
{
	size_t			i;
	bool			hit_flag;
	//t_shape			*nearest_shape;
	t_nearest		*nearest;
	t_intersection	i_point;
	t_intersection	nearest_point;

	nearest.flag = false;
	nearest_point.distance = max_d;
	i = 0;
	while (i < config.num_shapes)
	{
		hit_flag = is_hittable(config.shapes_list[i], ray, &i_point);
		if (hit_flag && i_point.distance < nearest_point.distance)
		{
			//nearest_shape = &config.shapes_list[i];
			nearest.shape = config.shapes_list[i];
			//nearest_shape.i_point = i_point;
			nearest.i_point = i_point;
			nearest.flag = true;
			if (shadow)
				break ;
		}
		i++;
	}
	//return (nearest_shape);
	return (nearest);
}

void	add_ambient_luminance(t_config config, t_color *color)
{
	color->r += config.ambient_illuminance.r * config.shapes_list->material.ambient_ref.r;
	color->g += config.ambient_illuminance.r * config.shapes_list->material.ambient_ref.r;
	color->b += config.ambient_illuminance.r * config.shapes_list->material.ambient_ref.r;
}

void	add_diffuse_luminance(t_shape shape, t_color illuminance, double normal_light_dir_dot, t_color *color)
{
	color->r += shape->material.diffuse_ref.r * illuminance.r * normal_light_dir_dot;
	color->g += shape->material.diffuse_ref.g * illuminance.g * normal_light_dir_dot;
	color->b += shape->material.diffuse_ref.b * illuminance.b * normal_light_dir_dot;
}

//void	add_specular_luminance(t_shape shape, t_color illuminance, t_vec light_dir, t_color *color)
//{
//	t_vec	specular_dir;
//	t_vec	rev_camera_to_screen_dir;
//	float	rev_camera_to_screen_specular_dot;
//
//	normal_light_dir_dot = dot(shape.i_point.normal, light_dir);
//	normal_light_dir_dot = rounding_num(normal_light_dir_dot, 0, 1);
//	specular_dir = normalize(sub(mul(2 * normal_light_dir_dot, shape.i_point.normal), light_dir));
//	rev_camera_to_screen_dir = normalize(mul(-1.0, )
//}

t_nearest	get_shadow_ray(t_config config, t_nearest nearest, t_vec light_dir)
{
	t_nearest	i_point_near;
	double		distance;
	t_ray		shadow_ray;

	distance = norm(sub(config.light.vec, nearest.i_point.pos)) - (1.0 / 512);
	shadow_ray.start = add(nearest.i_point, mul(1.0 / 512, light_dir));
	shadow_ray.direction = light_dir;
	i_point_near = get_nearest(config, shadow_ray, distance, 1);
	return (t_point);
}

t_color	get_luminance(t_cofig config, t_nearest nearest, t_ray ray)
{
	t_color		color;
	t_vec		light_dir;
	double		normal_light_dir_dot;
	//t_ray		shadow_ray;
	t_nearest	i_point_near;

	color = {0, 0, 0};
	add_ambient_luminance(config, &color);
	if (config.light == LT_POINT)
	{
		light_dir = normalize(sub(config.light.vec, nearest.i_point.pos));
	}
	else if (config.light == LT_DIRECTIONAL)
	{}

	i_point_near = 	get_shadow_ray();
//		get_nearest(config, shadow_ray, distance, 1);
	if (i_point_near.flag)
		return (color);

	//get_shadow_ray
	//if get_nearest
	//	return color;
	normal_light_dir_dot = dot(nearest.i_point.normal, light_dir);
	normal_light_dir_dot = rounding_num(normal_light_dir_dot, 0, 1);
	add_diffuse_luminance(nearest.shape, light.illuminance, normal_light_dir_dot, &color);
	if (normal_light_dir_dot > 0)
	{
		add_specular_luminance(nearest, light.illuminance, light_dir, &color);
	}
	return (color);
}

t_color	trace(t_cofig config, t_ray ray)
{
	bool			hit_flag;
	//t_shape			*shape;
	t_nearest		nearest;
	t_intersection	i_point; //add bool var is_hit
	t_color			color;
	
	color = {0, 0, 0}; //default color
	//shape = get_nearest(config, ray, DBL_MAX, 0);
	nearest = get_nearest(config, ray, DBL_MAX, 0);
	if (nearest.flag)
	{
		color = get_luminance(config, nearest, ray);
	}
	return (color);
}

void	ray_trace(t_camera *camera)
{
	size_t	x;
	size_t	y;
	t_ray	camera_ray;
	t_color	color;

	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			camera_ray = get_camera_ray(x, y, camera->pos);
			color = trace();
			draw(color);
			x++;
		}
		y++;
	}
}

int	main(void)
{
	init();
	ray_trace();
	destroy();
	return (0);
}
