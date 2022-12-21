#include "minirt.h"

#define HEIGHT 512
#define WIDTH 512

t_ray	get_camera_ray(size_t x, size_t y, t_vec camera_pos)
{
	t_ray	ray;
	t_vec	wp; //world_pos
//	double	wx;
//	double	wy;

	//Screen from the upper left origin to a rectangle of width and height 2.0 at the center origin
	wp.x = (2.0 * x) / (WIDTH - 1) - 1.0;
	wp.y = (-2.0 * y) / (HEIGHT - 1) + 1.0;
	wp.z = 0;
	
	//later change screen_camera_pos to world camera_pos
	ray.start = camera_pos;
	ray.direction.x = wp.x - camera_pos.x;
	ray.direction.x = wp.y - camera_pos.y;
	ray.direction.x = wp.z - camera_pos.z;
	return (ray);
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
			camera_ray = get_camera_ray(x, y, camera->pos);
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
