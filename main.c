#include "minirt.h"

#define HEIGHT 512
#define WIDTH 512

void	print_vector(t_vec vec, char *msg)
{
	printf("%s\n", msg);
	printf("x: %lf\n", vec.x);
	printf("y: %lf\n", vec.y);
	printf("z: %lf\n", vec.z);
}

void	get_basis_vector(t_vec *esx, t_vec *esy, t_vec cam_dir)
{
	if (cam_dir.x == 0 && cam_dir.z == 0 && cam_dir.y)
	{
		esx->x = 1.0;
		esx->y = 0.0;
		esx->z = 0.0;
		esy->x = 0.0;
		esy->y = 0.0;
		esy->z = 1.0;
		return ;
	}
	esx->x = cam_dir.z / sqrt(pow(cam_dir.z, 2) + pow(cam_dir.x, 2));
	esx->y = 0.0;
	esx->z = -(cam_dir.x) / sqrt(pow(cam_dir.z, 2) + pow(cam_dir.x, 2));
	*esx = normalize(*esx);
	*esy = normalize(cross(cam_dir, *esx));
}

t_ray	get_camera_ray(double x, double y, t_camera camera)
{
	t_ray	ray;
	t_vec	screen_pos;
	t_vec	esx;
	t_vec	esy;
	double	distance;
	t_vec	camera_to_screen_center;

	distance = (WIDTH / 2.0) / tan(camera.fov / 2 * M_PI / 180.0);
//
	camera_to_screen_center = mul(distance, camera.orientation);
//
	get_basis_vector(&esx, &esy, camera.orientation);
	//print_vector(esx, "esx");
	//print_vector(esy, "esy");
	//print_vector(mul(x - (WIDTH / 2), esx), "mul");
	//print_vector(mul((HEIGHT / 2 - y), esy), "mul2");
	screen_pos = add(mul(x - (WIDTH / 2), esx), mul((HEIGHT / 2 - y), esy));
	ray.start = camera.pos;
	ray.direction = normalize(add(screen_pos, camera_to_screen_center));



	//Screen from the upper left origin to a rectangle of width and height 2.0 at the center origin
//	wp.x = (2.0 * x) / (WIDTH - 1.0) - 1.0;
//	wp.y = (-2.0 * y) / (HEIGHT - 1.0) + 1.0;
//	wp.z = 0;
//	
//	//later change screen_camera_pos to world camera_pos
//	ray.start = camera.pos;
//	ray.direction.x = wp.x - camera.pos.x;
//	ray.direction.y = wp.y - camera.pos.y;
//	ray.direction.z = wp.z - camera.pos.z;
//	ray.start = camera_pos;
//	ray.direction.x = wp.x - camera_pos.x;
//	ray.direction.y = wp.y - camera_pos.y;
//	ray.direction.z = wp.z - camera_pos.z;
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

	sph_center_to_camera = sub(ray.start, sph.center);
	a = dot(ray.direction, ray.direction);
	b = 2.0 * dot(ray.direction, sph_center_to_camera);
	if (d == 0)
		return (-b / (2.0 * a));
	else if (d > 0)
	{
		t1 = (-b + sqrt(d)) / (2.0 * a);
		t2 = (-b - sqrt(d)) / (2.0 * a);
		if (t1 > 0 && (t2 < 0 || t1 < t2))
			return (t1);
		if (t2 > 0 && (t1 < 0 || t2 < t1))
			return (t2);
	}
	return (-1.0);
}

bool	is_hittable_sphere(t_sphere sph, t_ray ray, t_intersection *i_point)
{
	double	d;
	double	t;

	d = discriminant(sph, ray);
	t = get_solution_of_quadratic_equation(sph, ray, d);
	if (t > 0)
	{
		(*i_point).distance = t;
		(*i_point).pos = add(ray.start, mul(t, ray.direction));
		(*i_point).normal = normalize(sub((*i_point).pos, sph.center));
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
			(*i_point).distance = t;
			(*i_point).pos = add(ray.start, mul(t, ray.direction));
			(*i_point).normal = pln.normal;
			return (true);
		}
	}
	return (false);

}

double	cy_discriminant(t_cylinder cyl, t_ray ray, t_quadratic *quad)
{
	double	d;

	quad->a = pow(norm(cross(ray.direction, cyl.normal)), 2);
	quad->b = 2 * dot(cross(ray.direction, cyl.normal), cross(sub(ray.start, cyl.pos), cyl.normal));
	quad->c = pow(norm(cross(sub(ray.start, cyl.pos), cyl.normal)), 2) - pow(cyl.radius, 2);
	d = (quad->b * quad->b) - 4 * quad->a * quad->c;
	return (d);
}
double	cy_get_solution_of_quadratic_equation(double d, t_quadratic *quad)
{
	if (quad->a == 0)
		return (-1.0);
	if (d == 0)
	{
		quad->sol1 = -(quad->b) / (2.0 * quad->a);
		if (quad->sol1 > 0)
			return (-(quad->b) / (2.0 * quad->a));
		else
			return (-1.0);
	}
	else if (d > 0)
	{
		quad->sol1 = (-(quad->b) - sqrt(d)) / (2.0 * quad->a);
		quad->sol2 = (-(quad->b) + sqrt(d)) / (2.0 * quad->a);
		return (1.0);
	}
	return (-1.0);
//	return (quad->sol);
}

//t_intersection	*get_outside_inter(t_cylinder cyl, t_ray ray, double t, double pn_dot)
//{
//	t_intersection	*i_point;
//
//	(*i_point).distance = t;
//	(*i_point).pos = add(ray.start, mul(t, ray.direction));
//	(*i_point).normal = normalize(sub(sub((*i_point).pos, cyl.pos), 
//				mul(pn_dot, cyl.normal)));
//	return (i_point);
//}
//
//t_intersection	*get_indide_inter(t_cylinder cyl, t_ray ray, double t, double pn_dot)
//{
//	t_intersection	*i_point;
//
//	i_point->distance = t;
//	i_point->pos = add(ray.start, mul(t, ray.direction));
//	i_point->normal = normalize(sub(mul(pn_dot, cyl.normal), sub(i_point->pos, cyl.pos)));
//	return (i_point);
//}

bool	get_intersection(t_cylinder cyl, t_ray ray, t_quadratic quad, t_intersection *i_point)
{
	double	cy_pos_to_inter_cy_n_dot1;
	double	cy_pos_to_inter_cy_n_dot2;

	cy_pos_to_inter_cy_n_dot1 = dot(sub(add(ray.start, mul(quad.sol1, ray.direction)), cyl.pos), cyl.normal);
	cy_pos_to_inter_cy_n_dot2 = dot(sub(add(ray.start, mul(quad.sol2, ray.direction)), cyl.pos), cyl.normal);
	if (0 <= cy_pos_to_inter_cy_n_dot1 && cy_pos_to_inter_cy_n_dot1 <= cyl.height)
	{
//		i_point = get_outside_inter(cyl, ray, quad.sol1, cy_pos_to_inter_cy_n_dot1);
		(*i_point).distance = quad.sol1;
		(*i_point).pos = add(ray.start, mul(quad.sol1, ray.direction));
		(*i_point).normal = normalize(sub(sub((*i_point).pos, cyl.pos), 
				mul(cy_pos_to_inter_cy_n_dot1, cyl.normal)));
	}
	else if (0 <= cy_pos_to_inter_cy_n_dot2 && cy_pos_to_inter_cy_n_dot2 <= cyl.height)
	{
//		i_point = get_outside_inter(cyl, ray, quad.sol2, cy_pos_to_inter_cy_n_dot2);
		(*i_point).distance = quad.sol2;
		(*i_point).pos = add(ray.start, mul(quad.sol2, ray.direction));
		(*i_point).normal = normalize(sub(mul(cy_pos_to_inter_cy_n_dot2, cyl.normal), sub((*i_point).pos, cyl.pos)));
	}
	else
		return (false);
	return (true);
}

bool	is_hittable_cylinder(t_cylinder cyl, t_ray ray, t_intersection *i_point)
{
	double	d;
	double	t;
//	double	cy_pos_to_inter_cy_n_dot1;
//	double	cy_pos_to_inter_cy_n_dot2;
	t_quadratic	quad;

	d = cy_discriminant(cyl, ray, &quad);
	t = cy_get_solution_of_quadratic_equation(d, &quad);
	if (t > 0)
	{
		return (get_intersection(cyl, ray, quad, i_point));
//		cy_pos_to_inter_cy_n_dot1 = dot(sub(add(ray.start, mul(quad.sol1, ray.direction)), cyl.pos), cyl.normal);
//		cy_pos_to_inter_cy_n_dot2 = dot(sub(add(ray.start, mul(quad.sol2, ray.direction)), cyl.pos), cyl.normal);
//		if (0 <= cy_pos_to_inter_cy_n_dot1 && cy_pos_to_inter_cy_n_dot1 <= cyl.height)
//		{
//			i_point = get_outside_inter(cyl, ray, quad.sol1, cy_pos_to_inter_cy_n_dot1);
////			(*i_point).distance = quad.sol1;
////			(*i_point).pos = add(ray.start, mul(quad.sol1, ray.direction));
////			(*i_point).normal = normalize(sub(sub((*i_point).pos, cyl.pos), 
////					mul(cy_pos_to_inter_cy_n_dot1, cyl.normal)));
//		}
//		else if (0 <= cy_pos_to_inter_cy_n_dot2 && cy_pos_to_inter_cy_n_dot2 <= cyl.height)
//		{
//			i_point = get_outside_inter(cyl, ray, quad.sol2, cy_pos_to_inter_cy_n_dot2);
////			(*i_point).distance = quad.sol2;
////			(*i_point).pos = add(ray.start, mul(quad.sol2, ray.direction));
////			(*i_point).normal = normalize(sub(mul(cy_pos_to_inter_cy_n_dot2, cyl.normal), sub((*i_point).pos, cyl.pos)));
//		}
//		else
//			return (false);
//		return (true);
	}
	return (false);
}

bool	is_hittable(t_shape shape, t_ray ray, t_intersection *i_point)
{
	if (shape.type == ST_SPHERE)
		return (is_hittable_sphere(shape.sphere, ray, i_point));
	if (shape.type == ST_PLANE)
		return (is_hittable_plane(shape.plane, ray, i_point));
	if (shape.type == ST_CYLINDER)
		return (is_hittable_cylinder(shape.cylinder, ray, i_point));
//	if (shape.type == ST_SPHERE)
//		return (is_hittable_sphere(shape.sphere, ray, &i_point));
//	if (shape.type == ST_PLANE)
//		return (is_hittable_plane(shape.plane, ray, &i_point));
//	if (shape.type == ST_CYLINDER)
//		return (is_hittable_cylinder(shape.cylinder, ray, &i_point));
	return (false);
}

t_nearest	get_nearest(t_config config, t_ray ray, double max_d, bool shadow)
{
	bool			hit_flag;
	t_nearest		nearest;
	t_intersection	i_point;

	nearest.flag = false;
	nearest.i_point.distance = max_d;
	config.shape_list = config.shape_list->next;
	while (config.shape_list != NULL)
	{
		hit_flag = is_hittable(*(config.shape_list), ray, &i_point);
		if (hit_flag && i_point.distance > 0 
				&& i_point.distance < nearest.i_point.distance)
		{
			nearest.shape = *(config.shape_list);
			nearest.i_point = i_point;
			nearest.flag = true;
			if (shadow)
				break ;
		}
		config.shape_list = config.shape_list->next;
	}
	return (nearest);
}

t_color	add_color(t_color n, t_color m)
{
	t_color	color;

	color.r = n.r + m.r;
	color.g = n.g + m.g;
	color.b = n.b + m.b;
	return (color);
}

t_color	add_ambient_luminance(t_config config)
{
	t_color	color;

	color.r = config.ambient.ambient_illuminance.r * config.ambient.ambient_ref.r;
	color.g = config.ambient.ambient_illuminance.g * config.ambient.ambient_ref.g;
	color.b = config.ambient.ambient_illuminance.b * config.ambient.ambient_ref.b;
	return (color);
}

t_color	add_diffuse_luminance(t_shape shape, t_color illuminance, double normal_light_dir_dot)
{
	t_color color;

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

	color = add_ambient_luminance(config);
	light_dir = normalize(sub(config.light.vec, nearest.i_point.pos));
	i_point_near = 	get_shadow_ray(config, nearest, light_dir);
	if (i_point_near.flag)
		return (color);
	normal_light_dir_dot = dot(nearest.i_point.normal, light_dir);
	normal_light_dir_dot = rounding_num(normal_light_dir_dot, 0, 1);
	color = add_color(color, add_diffuse_luminance(nearest.shape, config.light.illuminance, normal_light_dir_dot));
	if (normal_light_dir_dot > 0)
	{
		(void)ray;
//		color = add_color(color, add_specular_luminance(nearest, config.light.illuminance, light_dir, ray));
	}
	return (color);
}

t_color	trace(t_config config, t_ray ray)
{
	t_nearest		nearest;
	t_color			color;
	
	color.r = 0;
	color.g = 0;
	color.b = 0;
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
	double	x;
	double	y;
//	size_t	x;
//	size_t	y;
	t_ray	camera_ray;
	t_color	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
//			camera_ray = get_camera_ray(x, y, config.camera.pos);
			camera_ray = get_camera_ray(x, y, config.camera);
			//break;
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
