#include "minirt.h"

bool	get_intersection(t_cylinder cyl, t_ray ray, t_quadratic quad, t_intersection *i_point)
{
	double	pos_to_i_n_dot1;
	double	pos_to_i_n_dot2;

	pos_to_i_n_dot1 = dot(sub(add(ray.start, mul(quad.sol1, ray.direction)), cyl.pos), cyl.normal);
	pos_to_i_n_dot2 = dot(sub(add(ray.start, mul(quad.sol2, ray.direction)), cyl.pos), cyl.normal);
	if (0 <= pos_to_i_n_dot1 && pos_to_i_n_dot1 <= cyl.height)
	{
//		i_point = get_outside_inter(cyl, ray, quad.sol1, cy_pos_to_inter_cy_n_dot1);
		(*i_point).distance = quad.sol1;
		(*i_point).pos = add(ray.start, mul(quad.sol1, ray.direction));
		(*i_point).normal = normalize(sub(sub((*i_point).pos, cyl.pos), \
				mul(pos_to_i_n_dot1, cyl.normal)));
	}
	else if (0 <= pos_to_i_n_dot2 && pos_to_i_n_dot2 <= cyl.height)
	{
//		i_point = get_outside_inter(cyl, ray, quad.sol2, cy_pos_to_inter_cy_n_dot2);
		(*i_point).distance = quad.sol2;
		(*i_point).pos = add(ray.start, mul(quad.sol2, ray.direction));
		(*i_point).normal = normalize(sub(mul(pos_to_i_n_dot2, cyl.normal), sub((*i_point).pos, cyl.pos)));
	}
	else
		return (false);
	return (true);
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

bool	is_hittable_cylinder(t_cylinder cyl, t_ray ray, t_intersection *i_point)
{
	double		d;
	double		t;
	t_quadratic	quad;

	d = cy_discriminant(cyl, ray, &quad);
	t = cy_get_solution_of_quadratic_equation(d, &quad);
	if (t > 0)
		return (get_intersection(cyl, ray, quad, i_point));
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
	return (false);
}
