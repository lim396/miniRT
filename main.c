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
	double	solution;

	d = discriminant(sph, ray);
	solution = get_solution_of_quadratic_equation(d);
	if (t > 0)
	{
		i_point->distance = solution;
		i_point->pos = add(ray.start, mul(solution, ray.direction));
		i_point->normal = normalize(sub(i_point->pos, sph.center));
		return (true);
	}
	return (false);
}

bool	is_hittable(t_shape shape, t_ray ray, t_intersection *i_point)
{
	if (shape.type == ST_SPHERE)
		return (is_hittable_sphere(shape, ray, i_point));
	if (shape.type == ST_PLANE)
		return (is_hittable_plane(shape, ray, i_point));
//	if (shape.type == ST_SYLINDER)
//		return (is_hittable_sylinder());

}

t_shape	get_nearest(t_cofig config, t_ray ray, double max_d, bool shadow)
{
	size_t			i;
	bool			hit_flag;
	t_shape			*nearest_shape;
	t_intersection	i_point;
	t_intersection	nearest_point;

	nearest_shape = NULL;
	nearest_point.distance = max_d;
	i = 0;
	while (i < config.num_shapes)
	{
		hit_flag = is_hittable(config.shapes[i], ray, &i_point);
		if (hit_flag && i_point.distance < nearest_point.distance)
		{
			nearest_shape = &config.shapes[i];
			nearest_shape.i_point = i_point;
			if (shadow)
				break ;
		}
		i++;
	}
	return (nearest_shape);
}

t_color	trace(t_cofig config, t_ray ray)
{
	bool			hit_flag;
	t_shape			*shape;
	t_intersection	i_point; //add bool var is_hit
	t_color			color;
	
	color = {0, 0, 0}; //default color
	shape = get_nearest(config, ray, DBL_MAX, 0);
	if (shape)
	{
		color = get_luminance();
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
