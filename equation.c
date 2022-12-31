#include "minirt.h"

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
	c = dot(sph_center_to_camera, sph_center_to_camera) \
		- sph.radius * sph.radius;
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

double	cy_discriminant(t_cylinder cyl, t_ray ray, t_quadratic *quad)
{
	double	d;

	quad->a = pow(norm(cross(ray.direction, cyl.normal)), 2);
	quad->b = 2 * dot(cross(ray.direction, cyl.normal), \
			cross(sub(ray.start, cyl.pos), cyl.normal));
	quad->c = pow(norm(cross(sub(ray.start, cyl.pos), cyl.normal)), 2) \
			- pow(cyl.radius, 2);
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
}
