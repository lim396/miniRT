#include "minirt.h"

#define HEIGHT 512
#define WIDTH 512

t_ray	camera_ray(x, double y, t_ray )
{
	double	wx;
	double	wy;

	wx = ;
	wy = ;
}

void	ray_trace(t_camera *camera)
{
	size_t	x;
	size_t	y;
	t_ray	camera_ray;
	t_color	color;

	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			camera_ray = get_ray(x, y, camera);
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
