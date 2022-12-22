#ifndef VEC_UTIL
#define VEC_UTIL

#include <math.h>
//#include "minirt.h"

typedef struct	s_vec
{
	double	x;
	double	y;
	double	z;
} t_vec;

t_vec	init(double x, double y, double z);
t_vec	add(t_vec a, t_vec b);
t_vec	sub(t_vec a, t_vec b);
t_vec	mul(double t, t_vec a);
double	rounding_num(double num, double min, double max);
double	dot(t_vec a, t_vec b);
double	squred_norm(t_vec a);
double	norm(t_vec a);
t_vec	normalize(t_vec a);
t_vec	cross(t_vec a, t_vec b);
#endif
