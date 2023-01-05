/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_shapes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shongou <shongou@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 23:34:28 by shongou           #+#    #+#             */
/*   Updated: 2023/01/04 23:34:29 by shongou          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	*new_node(int type, int *err_flag)
{
	t_shape	*node;

	node = (t_shape *)malloc(sizeof(t_shape) * 1);
	if (node == NULL)
	{
		*err_flag = MALLOC_ERROR;
		return (NULL);
	}
	node->type = type;
	node->next = NULL;
	return (node);
}

void	set_sphere(char **strs, t_config *config, int *err_flag, int *scene_obj)
{
	size_t	i;
	t_shape	*shape_node;

	*scene_obj |= SP;
	shape_node = new_node(ST_SPHERE, err_flag);
	if (shape_node == NULL)
		return ;
	i = 1;
	while (strs[i])
	{
		if (i == 1)
			shape_node->sphere.center = set_coordinates(strs[i], err_flag);
		else if (i == 2)
			shape_node->sphere.radius = set_size(strs[i], err_flag) / 2.0;
		else if (i == 3)
			shape_node->material.diffuse_ref = set_rgb(strs[i], err_flag);
		i++;
	}
	if (i != 4)
		*err_flag |= NUMBER_OF_ELEMENT_ERROR;
	add_list_last(&config->shape_list, shape_node);
}

void	set_cylinder(char **strs, t_config *config, int *err_flag, \
		int *scene_obj)
{
	size_t	i;
	t_shape	*shape_node;

	*scene_obj |= CY;
	shape_node = new_node(ST_CYLINDER, err_flag);
	if (shape_node == NULL)
		return ;
	i = 1;
	while (strs[i])
	{
		if (i == 1)
			shape_node->cylinder.pos = set_coordinates(strs[i], err_flag);
		else if (i == 2)
			shape_node->cylinder.normal = set_orientation(strs[i], err_flag);
		else if (i == 3)
			shape_node->cylinder.radius = set_size(strs[i], err_flag) / 2.0;
		else if (i == 4)
			shape_node->cylinder.height = set_size(strs[i], err_flag);
		else if (i == 5)
			shape_node->material.diffuse_ref = set_rgb(strs[i], err_flag);
		i++;
	}
	if (i != 6)
		*err_flag |= NUMBER_OF_ELEMENT_ERROR;
	add_list_last(&config->shape_list, shape_node);
}

void	set_plane(char **strs, t_config *config, int *err_flag, int *scene_obj)
{
	size_t	i;
	t_shape	*shape_node;

	*scene_obj |= PL;
	shape_node = new_node(ST_PLANE, err_flag);
	i = 1;
	while (strs[i])
	{
		if (i == 1)
			shape_node->plane.pos = set_coordinates(strs[i], err_flag);
		else if (i == 2)
			shape_node->plane.normal = set_orientation(strs[i], err_flag);
		else if (i == 3)
			shape_node->material.diffuse_ref = set_rgb(strs[i], err_flag);
		i++;
	}
	if (i != 4)
		*err_flag |= NUMBER_OF_ELEMENT_ERROR;
	add_list_last(&config->shape_list, shape_node);
}

//void	set_sphere(char **split_line, t_shape **shape_list)
//{
//	size_t	i;
//	t_shape	*shape_node;
//
//	shape_node = (t_shape *)malloc(sizeof(t_shape) * 1);
//	shape_node->type = ST_SPHERE;
//	shape_node->next = NULL;
//	i = 1;
//	while (split_line[i])
//	{
//		if (i == 1)
//			shape_node->sphere.center = set_vec(split_line[i]);
//		else if (i == 2)
//			shape_node->sphere.radius = atod(split_line[i]) / 2.0;
//		else if (i == 3)
//			shape_node->material.diffuse_ref = set_color(split_line[i]);
//		else
//			printf("ERROR\n");
//		i++;
//	}
//	add_list_last(shape_list, shape_node);
//}
//
//void	set_cylinder(char **split_line, t_shape **shape_list)
//{
//	size_t	i;
//	t_shape	*shape_node;
//
//	shape_node = (t_shape *)malloc(sizeof(t_shape) * 1);
//	shape_node->type = ST_CYLINDER;
//	shape_node->next = NULL;
//	i = 1;
//	while (split_line[i])
//	{
//		if (i == 1)
//			shape_node->cylinder.pos = set_vec(split_line[i]);
//		else if (i == 2)
//			shape_node->cylinder.normal= set_vec(split_line[i]);
//		else if (i == 3)
//			shape_node->cylinder.radius= atod(split_line[i]) / 2.0;
//		else if (i == 4)
//			shape_node->cylinder.height = atod(split_line[i]);
//		else if (i == 5)
//			shape_node->material.diffuse_ref = set_color(split_line[i]);
//		else
//			printf("ERROR\n");
//		i++;
//	}
//	add_list_last(shape_list, shape_node);
//}
//
//void	set_plane(char **split_line, t_shape **shape_list)
//{
//	size_t	i;
//	t_shape	*shape_node;
//
//	shape_node = (t_shape *)malloc(sizeof(t_shape) * 1);
//
//	shape_node->type = ST_PLANE;
//	shape_node->next = NULL;
//	i = 1;
//	while (split_line[i])
//	{
//		if (i == 1)
//			shape_node->plane.pos = set_vec(split_line[i]);
//		else if (i == 2)
//			shape_node->plane.normal = set_vec(split_line[i]);
//		else if (i == 3)
//			shape_node->material.diffuse_ref = set_color(split_line[i]);
//		else
//			printf("ERROR\n");
//		i++;
//	}
//	add_list_last(shape_list, shape_node);
//}
