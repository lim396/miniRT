#include "minirt.h"

t_color	add_color(t_color n, t_color m)
{
	t_color	color;

	color.r = n.r + m.r;
	color.g = n.g + m.g;
	color.b = n.b + m.b;
	return (color);
}

t_color	set_color(char *rgb)
{
	char	**split_rgb;
	t_color	color;

	split_rgb = ft_split(rgb, ',');
	if (split_rgb[0])
		color.r = atod(split_rgb[0]) / 255.0;
	//else
		//printf("ERROR\n");
	if (split_rgb[1])
		color.g = atod(split_rgb[1]) / 255.0;
	//else
		//printf("ERROR\n");
	if (split_rgb[2])
		color.b = atod(split_rgb[2]) / 255.0;
	//else
		//printf("ERROR\n");
	return (color);
}
