#include "minirt.h"

t_nearest	get_nearest(t_config config, t_ray ray, double max_d, bool shadow)
{
	bool			hit_flag;
	t_nearest		nearest;
	t_intersection	i_point;

	nearest.flag = false;
	nearest.i_point.distance = max_d;
	config.shape_list = config.shape_list->next;
	while (config.shape_list != NULL)
	{
		hit_flag = is_hittable(*(config.shape_list), ray, &i_point);
		if (hit_flag && i_point.distance > 0 \
				&& i_point.distance < nearest.i_point.distance)
		{
			nearest.shape = *(config.shape_list);
			nearest.i_point = i_point;
			nearest.flag = true;
			if (shadow)
				break ;
		}
		config.shape_list = config.shape_list->next;
	}
	return (nearest);
}
