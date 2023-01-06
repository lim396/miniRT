/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shongou <shongou@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 23:34:20 by shongou           #+#    #+#             */
/*   Updated: 2023/01/04 23:34:22 by shongou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_color	trace(t_config config, t_ray ray)
{
	t_nearest		nearest;
	t_color			color;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	nearest = get_nearest(config, ray, DBL_MAX, 0);
	if (nearest.flag)
		color = get_luminance(config, nearest, ray);
	return (color);
}

void	ray_trace(t_config config, t_status *status)
{
	double	x;
	double	y;
	t_ray	camera_ray;
	t_color	color;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			camera_ray = get_camera_ray(x, y, config.camera);
			color = trace(config, camera_ray);
			draw(color, (int)x, (int)y, status->img);
			x++;
		}
		y++;
	}
	status->config = config;
	mlx_key_hook(status->mlx_win, key_hook, status);
	mlx_hook(status->mlx_win, EXPOSE, 1L << 15, &rendering, status);
	mlx_hook(status->mlx_win, 33, 1 << 17, delete_window, status);
	mlx_loop(status->mlx);
}
