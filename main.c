/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shongou <shongou@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 23:33:59 by shongou           #+#    #+#             */
/*   Updated: 2023/01/04 23:34:01 by shongou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_config	config;
	t_status	*status;

	if (argc != 2)
	{
		ft_putstr_fd("Error\n", 2);
		ft_putstr_fd("\e[1;31m===Error===\e[0m\n", 2);
		ft_putstr_fd("No file specified or Too many files\n", 2);
		display_usage();
		return (1);
	}
	config = init_config(argv);
	status = mlx_run(config);
	ray_trace(config, status);
	return (0);
}
