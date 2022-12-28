#include "minirt.h"

t_color	add_color(t_color n, t_color m)
{
	t_color	color;

	color.r = n.r + m.r;
	color.g = n.g + m.g;
	color.b = n.b + m.b;
	return (color);
}

