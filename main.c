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
	wp.x = (2.0 * x) / (WIDTH - 1.0) - 1.0;
	wp.y = (-2.0 * y) / (HEIGHT - 1.0) + 1.0;
	wp.z = 0;
	
	//later change screen_camera_pos to world camera_pos
	ray.start = camera_pos;
	ray.direction.x = wp.x - camera_pos.x;
	ray.direction.y = wp.y - camera_pos.y;
	ray.direction.z = wp.z - camera_pos.z;
//	printf("%lf\n", wp.x);
//	printf("%lf\n", wp.y);
//	printf("%lf\n", wp.z);
//	printf("\n");
//	printf("%lf\n", camera_pos.x);
//	printf("%lf\n", camera_pos.y);
//	printf("%lf\n", camera_pos.z);
//	printf("\n");
//	printf("%lf\n", ray.direction.x);
//	printf("%lf\n", ray.direction.y);
//	printf("%lf\n", ray.direction.z);
//	printf("\n");
	return (ray);
}

double	discriminant(t_sphere sph, t_ray ray)
{
	t_vec	sph_center_to_camera;
	double	a;
	double	b;
	double	c;
	double	d;

	sph_center_to_camera = sub(ray.start, sph.center);
	a = dot(ray.direction, ray.direction);
	b = 2.0 * dot(ray.direction, sph_center_to_camera);
	c = dot(sph_center_to_camera, sph_center_to_camera) - sph.radius * sph.radius;
	d = (b * b) - 4.0 * a * c;
	return (d);	
}

double	get_solution_of_quadratic_equation(t_sphere sph, t_ray ray, double d)
{
	t_vec	sph_center_to_camera;
	double	a;
	double	b;
	double	t1;
	double	t2;

//	printf("%lf\n", ray.start.x);
//	printf("%lf\n", ray.start.y);
//	printf("%lf\n", ray.start.z);
//	printf("\n");
//	printf("%lf\n", sph.center.x);
//	printf("%lf\n", sph.center.y);
//	printf("%lf\n", sph.center.z);
//	printf("\n");
//	printf("%lf\n", sph.radius);
//	printf("\n");
//	printf("%fl\n", ray.direction.x);
//	printf("%fl\n", ray.direction.y);
//	printf("%fl\n", ray.direction.z);
//	printf("\n");
//	printf("\n");
//	printf("\n");
	sph_center_to_camera = sub(ray.start, sph.center);
	a = dot(ray.direction, ray.direction);
	b = 2.0 * dot(ray.direction, sph_center_to_camera);
	if (d == 0)
	{
//		printf("ok\n");
		return (-b / (2.0 * a));
	}
	else if (d > 0)
	{
//		printf("ok\n");
		t1 = (-b + sqrt(d)) / (2.0 * a);
		t2 = (-b - sqrt(d)) / (2.0 * a);
		if (t1 > 0)
		{
			if (t2 > 0 && t2 < t1)
				return (t2);
			return (t1);
		}
	}
//	printf("ko\n");
	return (-1.0);
}

bool	is_hittable_sphere(t_sphere sph, t_ray ray, t_intersection **i_point)
{
//	printf("ok\n");
	double	d;
	double	t;

	d = discriminant(sph, ray);
	t = get_solution_of_quadratic_equation(sph, ray, d);
	if (t > 0)
	{
//		printf("%lf\n", t);
		(*i_point)->distance = t;
		(*i_point)->pos = add(ray.start, mul(t, ray.direction));
		(*i_point)->normal = normalize(sub((*i_point)->pos, sph.center));
		return (true);
	}
	return (false);
}

bool	is_hittable_plane(t_plane pln, t_ray ray, t_intersection **i_point)
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
			(*i_point)->distance = t;
//			printf("%lf\n", ray.direction.x);
//			printf("%lf\n", ray.direction.y);
//			printf("%lf\n", ray.direction.z);
			(*i_point)->pos = add(ray.start, mul(t, ray.direction));
//			printf("%lf\n", i_point->pos.x);
//			printf("%lf\n", i_point->pos.y);
//			printf("%lf\n", i_point->pos.z);
			(*i_point)->normal = pln.normal;
			return (true);
		}
	}
	return (false);

}

bool	is_hittable(t_shape shape, t_ray ray, t_intersection *i_point)
{
	if (shape.type == ST_SPHERE)
		return (is_hittable_sphere(shape.sphere, ray, &i_point));
	if (shape.type == ST_PLANE)
		return (is_hittable_plane(shape.plane, ray, &i_point));
//	if (shape.type == ST_SYLINDER)
//		return (is_hittable_sylinder());
	return (false);
}

//t_shape	get_nearest(t_config config, t_ray ray, double max_d, bool shadow)
t_nearest	get_nearest(t_config config, t_ray ray, double max_d, bool shadow)
{
	//size_t			i;
	bool			hit_flag;
	//t_shape			*nearest_shape;
	t_nearest		nearest;
	t_intersection	i_point;
	t_shape	*list;
//	t_intersection	nearest_point;

	list = config.shape_list;
	nearest.flag = false;
	nearest.i_point.distance = max_d;
//	nearest_point.distance = max_d;
	//i = 0;
	//while (i < 2)//config.num_shapes)
	list = list->next;
	while (list != NULL)
	{
//		ft_memset(&i_point, 0, sizeof(t_intersection));
//		printf("type: %d\n", list->type);
		//hit_flag = is_hittable(config.shape_list[i], ray, &i_point);
//		t_intersection	i_point;
		hit_flag = is_hittable(*list, ray, &i_point);
//		if (hit_flag && list->type == ST_SPHERE)
//		if (hit_flag)
//		{
//			printf("%lf\n", i_point.pos.x);
//			printf("%lf\n", i_point.pos.y);
//			printf("%lf\n", i_point.pos.z);
//		}
//		printf("%d\n", hit_flag);
//		if (hit_flag && i_point.distance < nearest_point.distance)
		if (hit_flag && i_point.distance < nearest.i_point.distance)
		{
//			printf("ok\n");
			//nearest_shape = &config.shape_list[i];
			nearest.shape = *list;
			//nearest_shape.i_point = i_point;
			nearest.i_point = i_point;
			nearest.flag = true;
			if (shadow)
				break ;
		}
		list = list->next;
		//i++;
	}
	return (nearest);
//	config.shape_list = config.shape_list->next;
//	while (config.shape_list != NULL)
//	{
//		printf("type: %d\n", config.shape_list->type);
//		//hit_flag = is_hittable(config.shape_list[i], ray, &i_point);
//		hit_flag = is_hittable(*config.shape_list, ray, &i_point);
////		printf("%d\n", hit_flag);
////		if (hit_flag && i_point.distance < nearest_point.distance)
//		if (hit_flag && i_point.distance < nearest.i_point.distance)
//		{
////			printf("ok\n");
//			//nearest_shape = &config.shape_list[i];
//			nearest.shape = *config.shape_list;
//			//nearest_shape.i_point = i_point;
//			nearest.i_point = i_point;
//			nearest.flag = true;
//			if (shadow)
//				break ;
//		}
//		config.shape_list = config.shape_list->next;
//		//i++;
//	}
//	//return (nearest_shape);
}

t_color	add_color(t_color n, t_color m)
{
	t_color	color;
//	printf("diffu\n");
//	printf("%lf\n", m.r);
//	printf("%lf\n", m.g);
//	printf("%lf\n", m.b);
//	printf("\n");

	color.r = n.r + m.r;
	color.g = n.g + m.g;
	color.b = n.b + m.b;
	return (color);
}

t_color	add_ambient_luminance(t_config config)
{
	t_color	color;

//	printf("add ambi ill\n");
//	printf("%lf\n", config.ambient.ambient_illuminance.r);
//	printf("%lf\n", config.ambient.ambient_illuminance.g);
//	printf("%lf\n", config.ambient.ambient_illuminance.b);
//	printf("add ambi ref\n");
//	printf("%lf\n", config.ambient.ambient_ref.r);
//	printf("%lf\n", config.ambient.ambient_ref.g);
//	printf("%lf\n", config.ambient.ambient_ref.b);
//	printf("\n");
	color.r = config.ambient.ambient_illuminance.r * config.ambient.ambient_ref.r;
	color.g = config.ambient.ambient_illuminance.g * config.ambient.ambient_ref.g;
	color.b = config.ambient.ambient_illuminance.b * config.ambient.ambient_ref.b;
	return (color);
}

t_color	add_diffuse_luminance(t_shape shape, t_color illuminance, double normal_light_dir_dot)
{
	t_color color;
//	double	normal_light_dir_dot;

//	normal_light_dir_dot = dot(nearest.i_point.normal, light_dir);
//	normal_light_dir_dot = rounding_num(normal_light_dir_dot, 0, 1);
//	printf("shape diffuse\n");
//	printf("%lf\n", shape.material.diffuse_ref.r);
//	printf("%lf\n", shape.material.diffuse_ref.b);
//	printf("%lf\n", shape.material.diffuse_ref.g);
//	printf("\n");
//	printf("%lf\n", illuminance.r);
//	printf("%lf\n", illuminance.g);
//	printf("%lf\n", illuminance.b);
//	printf("\n");
//	printf("%lf\n", normal_light_dir_dot);
//	printf("col\n");
//	printf("%lf\n", color.r);
//	printf("%lf\n", color.g);
//	printf("%lf\n", color.b);
//	printf("\n");
	color.r = shape.material.diffuse_ref.r * illuminance.r * normal_light_dir_dot;
	color.g = shape.material.diffuse_ref.g * illuminance.g * normal_light_dir_dot;
	color.b = shape.material.diffuse_ref.b * illuminance.b * normal_light_dir_dot;
	return (color);
}

t_color	add_specular_luminance(t_nearest nearest, t_color illuminance, t_vec light_dir, t_ray camera_ray)
{
	t_vec	specular_dir;
	t_vec	rev_camera_to_screen_dir;
	float	rev_camera_to_screen_specular_dot;
	t_color	color;
	double	normal_light_dir_dot;

	normal_light_dir_dot = dot(nearest.i_point.normal, light_dir);
	normal_light_dir_dot = rounding_num(normal_light_dir_dot, 0, 1);
	specular_dir = normalize(sub(mul(2 * normal_light_dir_dot, nearest.i_point.normal), light_dir));
	rev_camera_to_screen_dir = normalize(mul(-1.0, camera_ray.direction));
	rev_camera_to_screen_specular_dot = dot(specular_dir, rev_camera_to_screen_dir);
	rev_camera_to_screen_specular_dot = rounding_num(rev_camera_to_screen_specular_dot, 0, 1);
	color.r = nearest.shape.material.specular_ref.r * illuminance.r * pow(rev_camera_to_screen_specular_dot, SHININESS);
	color.g = nearest.shape.material.specular_ref.g * illuminance.g * pow(rev_camera_to_screen_specular_dot, SHININESS);
	color.b = nearest.shape.material.specular_ref.b * illuminance.b * pow(rev_camera_to_screen_specular_dot, SHININESS);
	return (color);
}

t_nearest	get_shadow_ray(t_config config, t_nearest nearest, t_vec light_dir)
{
	t_nearest	i_point_near;
	double		distance;
	t_ray		shadow_ray;

	distance = norm(sub(config.light.vec, nearest.i_point.pos)) - (1.0 / 512);
//	printf("distance %lf\n", distance);
	shadow_ray.start = add(nearest.i_point.pos, mul(1.0 / 512, light_dir));
	shadow_ray.direction = light_dir;
	i_point_near = get_nearest(config, shadow_ray, distance, 1);
	return (i_point_near);
}

t_color	get_luminance(t_config config, t_nearest nearest, t_ray ray)
{
	t_color		color;
	t_vec		light_dir;
	double		normal_light_dir_dot;
	t_nearest	i_point_near;

//	color = {0, 0, 0};
	color = add_ambient_luminance(config);
//	printf("get ambi\n");
//	printf("%lf\n", color.r);
//	printf("%lf\n", color.g);
//	printf("%lf\n", color.b);
//	printf("\n");
//	printf("%lf\n", config.light.vec.x);
//	printf("%lf\n", config.light.vec.y);
//	printf("%lf\n", config.light.vec.z);
//	printf("%lf\n", nearest.i_point.pos.x);
//	printf("%lf\n", nearest.i_point.pos.y);
//	printf("%lf\n", nearest.i_point.pos.z);
//	printf("%lf\n", nearest.shape.sphere.center.z);
	light_dir = normalize(sub(config.light.vec, nearest.i_point.pos));
//	if (config.light.type == POINT)
//	{
//	}
//	else if (config.light.type == DIRECTIONAL)
//	{
//		light_dir = normalize(sub(config.light.vec, nearest.i_point.pos));
//	}

	i_point_near = 	get_shadow_ray(config, nearest, light_dir);
//	printf("%d\n", i_point_near.flag);
	if (i_point_near.flag)
		return (color);
	normal_light_dir_dot = dot(nearest.i_point.normal, light_dir);
	normal_light_dir_dot = rounding_num(normal_light_dir_dot, 0, 1);
	color = add_color(color, add_diffuse_luminance(nearest.shape, config.light.illuminance, normal_light_dir_dot));
//	printf("diffu\n");
//	printf("%lf\n", color.r);
//	printf("%lf\n", color.g);
//	printf("%lf\n", color.b);
//	printf("\n");
	if (normal_light_dir_dot > 0)
	{
		(void)ray;
//		color = add_color(color, add_specular_luminance(nearest, config.light.illuminance, light_dir, ray));
	}
	return (color);
}

t_color	trace(t_config config, t_ray ray)
{
//	bool			hit_flag;
	//t_shape			*shape;
	t_nearest		nearest;
//	t_intersection	i_point; //add bool var is_hit
	t_color			color = {0.0, 0.0, 0.0}; //default color;
	
//	color = {0.0, 0.0, 0.0}; //default color
	//shape = get_nearest(config, ray, DBL_MAX, 0);
	nearest = get_nearest(config, ray, DBL_MAX, 0);
	if (nearest.flag)
	{
//		printf("ERROR2\n");
		color = get_luminance(config, nearest, ray);
	}
	return (color);
}

void	draw(t_color color)
{
//	(void)color;
//	double	r;
//	double	g;
//	double	b;
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;

	r = 255 * rounding_num(color.r, 0, 1);
	g = 255 * rounding_num(color.g, 0, 1);
	b = 255 * rounding_num(color.b, 0, 1);
	printf("%d %d %d\n", r, g, b);
}

void	ray_trace(t_config config)
{
	size_t	x;
	size_t	y;
	t_ray	camera_ray;
	t_color	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			camera_ray = get_camera_ray(x, y, config.camera.pos);
			color = trace(config, camera_ray);
			draw(color);
			x++;
		}
		y++;
	}
}

int	main(int argc, char **argv)
{
	t_config	config;
	if (argc != 2)
		return (1);

	//tmp
	printf("P3\n");
	printf("%d %d\n", WIDTH, HEIGHT);
	printf("255\n");
	//////

	config = init_config(argv);
	ray_trace(config);
//	destroy();
	return (0);
}
