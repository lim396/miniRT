/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_ray.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shongou <shongou@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 23:32:58 by shongou           #+#    #+#             */
/*   Updated: 2023/01/04 23:33:01 by shongou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	distance = (WIDTH / 2.0) / tan(camera.fov / 2 * M_PI / 180.0);
	get_basis_vector(&esx, &esy, camera.orientation);
	screen_pos = add(mul(x - (WIDTH / 2), esx), mul((HEIGHT / 2 - y), esy));
	ray.start = camera.pos;
	ray.direction \
		= normalize(add(screen_pos, mul(distance, camera.orientation)));
	return (ray);
}
