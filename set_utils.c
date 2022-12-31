#include "minirt.h"

t_color	set_rgb(char *str, int *err_flag)
{
	t_color	color;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	if (!valid_color(str))
	{
		*err_flag |= INVALID_COLOR;
		return (color);
	}
	color = set_color(str);
	/*
	if (0 > color.r || 255 < color.r)
		*err_flag |= INVALID_COLOR;
	if (0 > color.g || 255 < color.g)
		*err_flag |= INVALID_COLOR;
	if (0 > color.b || 255 < color.b)
		*err_flag |= INVALID_COLOR;
	*/
	if (0 > color.r || 1.0 < color.r)
		*err_flag |= INVALID_COLOR;
	if (0 > color.g || 1.0 < color.g)
		*err_flag |= INVALID_COLOR;
	if (0 > color.b || 1.0 < color.b)
		*err_flag |= INVALID_COLOR;
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
		//*err_flag = 1;
		*err_flag |= INVALID_VECTOR;
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
		//*err_flag = 1;
		*err_flag |= INVALID_ORIENTATION;
		return (vec);
	}
	vec = set_vec(str);
	if (vec.x < -1.0 || 1.0 < vec.x)
		//*err_flag = 1;
		*err_flag |= INVALID_ORIENTATION;
	if (vec.y < -1.0 || 1.0 < vec.y)
		//*err_flag = 1;
		*err_flag |= INVALID_ORIENTATION;
	if (vec.z < -1.0 || 1.0 < vec.z)
		//*err_flag = 1;
		*err_flag |= INVALID_ORIENTATION;
	if (vec.x == 0.0 && vec.y == 0.0 && vec.z == 0.0)
		*err_flag |= INVALID_ORIENTATION;
		//*err_flag = 1;
	return (vec);
}

double	set_fov(char *str, int *err_flag)
{
	double	fov;

	if (!valid_digit(str))
	{
		//*err_flag = 1;
		*err_flag |= INVALID_FOV;
		return (0);
	}
	fov = atod(str);
	if (fov < 0.0 && 180.0 < fov)
		*err_flag |= INVALID_FOV;
		//*err_flag = 1;
	return (fov);
}

double	set_ratio(char *str, int *err_flag)
{
	double	ratio;

	if (!valid_float(str))
	{
		//*err_flag = 1;
		*err_flag |= INVALID_RATIO;
		return (0);
	}
	ratio = atod(str);
	if (ratio < 0.0 && 1.0 < ratio)
		//*err_flag = 1;
		*err_flag |= INVALID_RATIO;
	return (ratio);
}

double	set_size(char *str, int *err_flag)
{
	double	size;

	if (!valid_float(str))
	{
		//*err_flag = 1;
		*err_flag |= INVALID_SIZE;
		return (0);
	}
	size = atod(str);
	if (size < 0.0)
		//*err_flag = 1;
		*err_flag |= INVALID_SIZE;
	return (size);
}
