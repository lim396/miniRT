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
	color = set_color(str, err_flag);
//	color = set_color(str);
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
		*err_flag |= INVALID_VECTOR;
		return (vec);
	}
	vec = set_vec(str, err_flag);
//	vec = set_vec(str);
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
		*err_flag |= INVALID_ORIENTATION;
		return (vec);
	}
	vec = set_vec(str, err_flag);
//	vec = set_vec(str);
	if (vec.x < -1.0 || 1.0 < vec.x)
		*err_flag |= INVALID_ORIENTATION;
	if (vec.y < -1.0 || 1.0 < vec.y)
		*err_flag |= INVALID_ORIENTATION;
	if (vec.z < -1.0 || 1.0 < vec.z)
		*err_flag |= INVALID_ORIENTATION;
	if (vec.x == 0.0 && vec.y == 0.0 && vec.z == 0.0)
		*err_flag |= INVALID_ORIENTATION;
	return (vec);
}
