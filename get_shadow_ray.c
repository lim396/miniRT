#include "minirt.h"

t_nearest	get_shadow_ray(t_config config, t_nearest nearest, t_vec light_dir)
{
	t_nearest	i_point_near;
	double		distance;
	t_ray		shadow_ray;

	distance = norm(sub(config.light.vec, nearest.i_point.pos)) - (1.0 / 512);
	shadow_ray.start = add(nearest.i_point.pos, mul(1.0 / 512, light_dir));
	shadow_ray.direction = light_dir;
	i_point_near = get_nearest(config, shadow_ray, distance, 1);
	return (i_point_near);
}
