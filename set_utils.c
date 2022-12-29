#include "minirt.h"

t_color	set_rgb(char *str, int *err_flag)
{
	t_color	color;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	if (!valid_color(str))
	{
		*err_flag = 1;
		return (color);
	}
	color = set_color(str);
	if (0 > color.r || 255 < color.r)
		return ();
	if (0 > color.g || 255 < color.g)
		return ();
	if (0 > color.b || 255 < color.b)
		return ();
	return (color);
}

t_vec	set_coordinates(char *str, int *err_flag)
{
	t_vec	vec;

	vec.x = 0;
	vec.y = 0;
	vec.z = 0;
	if (!valid_vector(str))
	{
		*err_flag = 1;
		return (vec);
	}
	vec = set_vec(str);
	return (vec);
}

t_vec	set_orientation(char *str, int *err_flag)
{
	t_vec	vec;

	vec.x = 0;
	vec.y = 0;
	vec.z = 0;
	if (!valid_vector(str))
	{
		*err_flag = 1;
		return (vec);
	}
	vec = set_vec(str);
	if (vec.x < -1.0 || 1.0 < vec.x)
		return ();
	if (vec.y < -1.0 || 1.0 < vec.y)
		return ();
	if (vec.z < -1.0 || 1.0 < vec.z)
		return ();
	if (vec.x == 0.0 && vec.y == 0.0 && vec.z == 0.0)
		return ();
	return (vec);
}

double	set_fov(char *str, int *err_flag)
{
	double	fov;

	if (!valid_digit(str))
	{
		*err_flag = 1;
		return (0);
	}
	fov = atod(str);
	if (0.0 <= fov && fov <= 180.0)
		return (fov);
	return ();
}

double	set_ratio(char *str, int *err_flag)
{
	double	ratio;

	if (!valid_float)
	{
		*err_flag = 1;
		return (0);
	}
	ratio = atod(str);
	if (0.0 <= ratio && ratio <= 1.0)
		return (ratio);
	return ();
}

double	set_size(char *str, int *err_flag)
{
	double	size;

	if (!valid_float)
	{
		*err_flag = 1;
		return (0);
	}
	size = atod(str);
	if (size > 0.0)
		return (size);
	return ();
}
