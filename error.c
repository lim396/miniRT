/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shongou <shongou@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 23:33:27 by shongou           #+#    #+#             */
/*   Updated: 2023/01/04 23:33:30 by shongou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	display_usage(void)
{
	ft_putstr_fd("\e[1;33m===Usage===\e[0m\n", 2);
	ft_putstr_fd("Please specify only one .rt file\n", 2);
	ft_putstr_fd("The following is the format\n", 2);
	ft_putstr_fd("Elements which are defined by a capital letter ", 2);
	ft_putstr_fd("can only be declared once\n", 2);
	ft_putstr_fd("Identifier [A] ambient lighting ratio [0.0,1.0] ", 2);
	ft_putstr_fd("RGB [0,255],[0,255],[0,255]\n", 2);
	ft_putstr_fd("Identifier [C] x,y,z coordinates [x],[y],[z] ", 2);
	ft_putstr_fd("3d normalized orientation vector [-1,1],[-1,1],[-1,1] ", 2);
	ft_putstr_fd("FOV [0,180]\n", 2);
	ft_putstr_fd("Identifier [L] x,y,z coordinates [x],[y],[z] ", 2);
	ft_putstr_fd("light brightness ratio[0.6], ", 2);
	ft_putstr_fd("RGB [0,255],[0,255],[0,255]\n", 2);
	ft_putstr_fd("Identifier [sp] x,y,z coordinates [x],[y],[z] ", 2);
	ft_putstr_fd("shape diameter [d], RGB [0,255],[0,255],[0,255]\n", 2);
	ft_putstr_fd("Identifier [pl] x,y,z coordinates [x],[y],[z] ", 2);
	ft_putstr_fd("normalized orientation vector [-1,1], ", 2);
	ft_putstr_fd("RGB [0,255],[0,255],[0,255]\n", 2);
	ft_putstr_fd("Identifier [cy] x,y,z coordinates [x],[y],[z] ", 2);
	ft_putstr_fd("normalized orientation vector [-1,1], ", 2);
	ft_putstr_fd("cylinder diameter [d], ", 2);
	ft_putstr_fd("cylinder height [h], RGB [0,255],[0,255],[0,255]\n", 2);
}

void	display_error(int error_flag)
{
	if (error_flag & OPEN_ERROR)
		ft_putstr_fd("open error\n", 2);
	if (error_flag & MALLOC_ERROR)
		ft_putstr_fd("malloc error\n", 2);
	if (error_flag & IDENTIFIER_ERROR)
		ft_putstr_fd("identifier error\n", 2);
	if (error_flag & NUMBER_OF_ELEMENT_ERROR)
		ft_putstr_fd("number of elements is incorrect or duplicate\n", 2);
	if (error_flag & NULL_STR)
		ft_putstr_fd("str is null\n", 2);
	if (error_flag & INVALID_COLOR)
		ft_putstr_fd("color is incorrect\n", 2);
	if (error_flag & INVALID_VECTOR)
		ft_putstr_fd("vector is incorrect\n", 2);
	if (error_flag & INVALID_ORIENTATION)
		ft_putstr_fd("orientation is incorrect\n", 2);
	if (error_flag & INVALID_FOV)
		ft_putstr_fd("fov is incorrect\n", 2);
	if (error_flag & INVALID_RATIO)
		ft_putstr_fd("ratio is incorrect\n", 2);
	if (error_flag & INVALID_SIZE)
		ft_putstr_fd("size is incorrect\n", 2);
	if (error_flag & INVALID_FILE)
		ft_putstr_fd("file ext is incorrect\n", 2);
}

void	error_handler(int fd, char *line, size_t line_n, int error_flag)
{
	if (fd >= 0)
		close(fd);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("\e[1;31m===Error===\e[0m\n", 2);
	if (line_n > 0)
	{
		ft_putstr_fd("line ", 2);
		if (line_n <= INT_MAX)
			ft_putnbr_fd(line_n, 2);
		else
			ft_putstr_fd("over INT_MAX", 2);
		ft_putstr_fd(": ", 2);
		ft_putendl_fd(line, 2);
	}
	free(line);
	display_error(error_flag);
	display_usage();
	exit(1);
}

void	before_set_config_err_handler(int err_flag)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("\e[1;31m===Error===\e[0m\n", 2);
	display_error(err_flag);
	exit(1);
}

void	check_obj(int scene_objs)
{
	if ((scene_objs & C) && (scene_objs & A) && (scene_objs & L) \
		&& ((scene_objs & SP) || (scene_objs & PL) || (scene_objs & CY)))
		return ;
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd("\e[1;31m===Error===\e[0m\n", 2);
	ft_putstr_fd("not enough objects\n", 2);
	display_usage();
	exit(1);
}
