#include "minirt.h"

void	get_basis_vector(t_vec *esx, t_vec *esy, t_vec cam_dir)
{
	if (cam_dir.x == 0 && cam_dir.z == 0 && cam_dir.y)
	{
		esx->x = 1.0;
		esx->y = 0.0;
		esx->z = 0.0;
		esy->x = 0.0;
		esy->y = 0.0;
		esy->z = 1.0;
		return ;
	}
	esx->x = cam_dir.z / sqrt(pow(cam_dir.z, 2) + pow(cam_dir.x, 2));
	esx->y = 0.0;
	esx->z = -(cam_dir.x) / sqrt(pow(cam_dir.z, 2) + pow(cam_dir.x, 2));
	*esx = normalize(*esx);
	*esy = normalize(cross(cam_dir, *esx));
}

t_ray	get_camera_ray(double x, double y, t_camera camera)
{
	t_ray	ray;
	t_vec	screen_pos;
	t_vec	esx;
	t_vec	esy;
	double	distance;
	t_vec	camera_to_screen_center; //cut?

	distance = (WIDTH / 2.0) / tan(camera.fov / 2 * M_PI / 180.0);
	camera_to_screen_center = mul(distance, camera.orientation);
	get_basis_vector(&esx, &esy, camera.orientation);
	screen_pos = add(mul(x - (WIDTH / 2), esx), mul((HEIGHT / 2 - y), esy));
	ray.start = camera.pos;
	ray.direction = normalize(add(screen_pos, camera_to_screen_center));
	return (ray);
}
