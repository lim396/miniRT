/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shongou <shongou@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 23:35:12 by shongou           #+#    #+#             */
/*   Updated: 2023/01/04 23:35:14 by shongou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	rendering(t_status *status)
{
	mlx_put_image_to_window(status->mlx, status->mlx_win, \
			status->img.img_ptr, 0, 0);
	return (0);
}

int	delete_window(t_status *status)
{
	mlx_destroy_image(status->mlx, status->img.img_ptr);
	mlx_destroy_window(status->mlx, status->mlx_win);
	mlx_destroy_display(status->mlx);
	status->img.img_ptr = NULL;
	status->mlx_win = NULL;
	status->mlx = NULL;
	exit(0);
}

void	free_list(t_config config)
{
	while (config.shape_list)
	{
		free(config.shape_list);
		config.shape_list = config.shape_list->next;
	}
}

int	key_hook(int key, t_status *status)
{
	if (key == ESC_KEY)
	{
		free_list(status->config);
		delete_window(status);
	}
	mlx_put_image_to_window(status->mlx, status->mlx_win, \
			status->img.img_ptr, 0, 0);
	return (0);
}

t_status	*mlx_run(t_config config)
{
	t_status	*status;

	status = (t_status *)malloc(sizeof(t_status) * 1);
	if (status == NULL)
		mlx_error(status, config, MALLOC_ERROR);
	status->mlx = mlx_init();
	if (status->mlx == NULL)
		mlx_error(status, config, MLX_INIT_ERR);
	status->mlx_win = mlx_new_window(status->mlx, WIDTH, HEIGHT, "miniRT");
	if (status->mlx_win == NULL)
		mlx_error(status, config, NEW_WINDOW_ERR);
	status->img.img_ptr = mlx_new_image(status->mlx, WIDTH, HEIGHT);
	if (status->img.img_ptr == NULL)
		mlx_error(status, config, NEW_IMAGE_ERR);
	status->img.addr = \
		mlx_get_data_addr(status->img.img_ptr, \
				&status->img.bpp, &status->img.size_line, &status->img.endian);
	return (status);
}
