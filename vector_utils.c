#include "minirt.h"

t_vec	init(double x, double y, double z)
{
	t_vec	vec;
	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

t_vec	add(t_vec a, t_vec b)
{
	t_vec	vec;
	vec.x = a.x + b.x;
	vec.y = a.y + b.y;
	vec.z = a.z + b.z;
	return (vec);
}

t_vec	sub(t_vec a, t_vec b)
{
	t_vec	vec;
	vec.x = a.x - b.x;
	vec.y = a.y - b.y;
	vec.z = a.z - b.z;
	return (vec);
}

t_vec mul(double t, t_vec a)
{
	t_vec	vec;
	vec.x = a.x * t;
	vec.y = a.y * t;
	vec.z = a.z * t;
	return (vec);
}

double	rounding_num(double num, double min, double max)
{
	double	n;

	n = num;
	if (num < min)
		n = min;
	if (num > max)
		n = max;
	return (n);
}

double	dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

double	squred_norm(t_vec a)
{
	return (a.x * a.x + a.y * a.y + a.z * a.z);
}

double	norm(t_vec a)
{
	return sqrt(squred_norm(a));
}

t_vec	normalize(t_vec a)
{
	t_vec	vec;
	double	vnorm;

	vnorm = norm(a);
	vec.x = a.x / vnorm;
	vec.y = a.y / vnorm;
	vec.z = a.z / vnorm;
	return (vec);
}

t_vec	cross(t_vec a, t_vec b)
{
	t_vec	vec;
	vec.x = a.y * b.z - a.z * b.y;
	vec.y = a.z * b.x - a.x * b.z;
	vec.z = a.x * b.y - a.y * b.x;
	return (vec);
}
