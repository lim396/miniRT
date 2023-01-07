/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shongou <shongou@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 23:34:16 by shongou           #+#    #+#             */
/*   Updated: 2023/01/04 23:34:18 by shongou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_mlx_error(int flag)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("\e[1;31m===Error===\e[0m\n", 2);
	if (flag & MLX_INIT_ERR)
		printf("mlx_init_error\n");
	if (flag & NEW_WINDOW_ERR)
		printf("mlx_new_window_error\n");
	if (flag & NEW_IMAGE_ERR)
		printf("mlx_new_image_error\n");
}

void	mlx_error(t_status *status, t_config config, int flag)
{
	free_list(config);
	if (status == NULL)
		before_set_config_err_handler(flag);
	print_mlx_error(flag);
	if (status->img.img_ptr)
		mlx_destroy_image(status->mlx, status->img.img_ptr);
	if (status->mlx_win)
		mlx_destroy_window(status->mlx, status->mlx_win);
	if (status->mlx)
		mlx_destroy_display(status->mlx);
	exit(1);
}
