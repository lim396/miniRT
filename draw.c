#include "minirt.h"

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
