#include "minirt.h"

#define HEIGHT 512
#define WIDTH 512

void	ray_trace()
{
	size_t	x;
	size_t	y;
	ray_t	camera_ray;
	color_t	color;

	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			camera_ray = get_ray();
			color = trace();
			draw(color);
			x++;
		}
		y++;
	}
}

int	main(void)
{
	init();
	ray_trace();
	destroy();
	return (0);
}
