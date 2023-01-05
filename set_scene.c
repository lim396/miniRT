/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_scene.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shongou <shongou@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 23:34:24 by shongou           #+#    #+#             */
/*   Updated: 2023/01/04 23:34:25 by shongou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_ambient(char **strs, t_config *config, int *err_flag, \
		int *scene_obj)
{
	size_t	i;

	*scene_obj |= A;
	i = 1;
	while (strs[i])
	{
		if (i == 1)
		{
			config->ambient.ambient_ref.r = set_ratio(strs[i], err_flag);
			config->ambient.ambient_ref.g = set_ratio(strs[i], err_flag);
			config->ambient.ambient_ref.b = set_ratio(strs[i], err_flag);
		}
		else if (i == 2)
			config->ambient.ambient_illuminance = set_rgb(strs[i], err_flag);
//		else
//			*err_flag |= NUMBER_OF_ELEMENT_ERROR;
		i++;
	}
	if (i != 3)
		*err_flag |= NUMBER_OF_ELEMENT_ERROR;
}

void	set_light(char **strs, t_config *config, int *err_flag, int *scene_obj)
{
	size_t	i;

	i = 1;
	*scene_obj |= L;
	while (strs[i])
	{
		if (i == 1)
			config->light.vec = set_coordinates(strs[i], err_flag);
		else if (i == 2)
			config->light.brightness_ratio = set_ratio(strs[i], err_flag);
		else if (i == 3)
			config->light.illuminance = set_rgb(strs[i], err_flag);
//		else
//			*err_flag |= NUMBER_OF_ELEMENT_ERROR;
		i++;
	}
	if (i != 4)
		*err_flag |= NUMBER_OF_ELEMENT_ERROR;
}

void	set_camera(char **strs, t_config *config, int *err_flag, int *scene_obj)
{
	size_t	i;

	i = 1;
	*scene_obj |= C;
	while (strs[i])
	{
		if (i == 1)
			config->camera.pos = set_coordinates(strs[i], err_flag);
		else if (i == 2)
			config->camera.orientation = set_orientation(strs[i], err_flag);
		else if (i == 3)
			config->camera.fov = set_fov(strs[i], err_flag);
//		else
//			*err_flag |= NUMBER_OF_ELEMENT_ERROR;
		i++;
	}
	if (i != 4)
		*err_flag |= NUMBER_OF_ELEMENT_ERROR;
}

//void	set_ambient(char **split_line, t_config *config)
//{
//	size_t	i;
//
//	i = 1;
//	while (split_line[i])
//	{
//		if (i == 1)
//		{
////			if (!valid_color(split_line[i]))
////				return (false);
//			config->ambient.ambient_ref = set_color(split_line[i]);
//		}
//		else if (i == 2)
//			config->ambient.ambient_illuminance = set_color(split_line[i]);
//		else
//			printf("ERROR\n");
//		i++;
//	}
////	return (true);
//}
//
//void	set_light(char **split_line, t_config *config)
//{
//	size_t	i;
//
//	i = 1;
//	while (split_line[i])
//	{
//		if (i == 1)
//			config->light.vec = set_vec(split_line[i]);
//		else if (i == 2)
//			config->light.brightness_ratio = atod(split_line[i]);
//		else if (i == 3)
//			config->light.illuminance = set_color(split_line[i]);
//		else
//			printf("ERROR\n");
//		i++;
//	}
//}
//
//void	set_camera(char **split_line, t_config *config)
//{
//	size_t	i;
//
//	i = 1;
//	while (split_line[i])
//	{
//		if (i == 1)
//			config->camera.pos = set_vec(split_line[i]);
//		else if (i == 2)
//			config->camera.orientation = set_vec(split_line[i]);
//		else if (i == 3)
//			config->camera.fov = atod(split_line[i]);
//		else
//			printf("ERROR\n");
//		i++;
//	}
//}
