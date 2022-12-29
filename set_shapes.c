#include "minirt.h"

//void	set_sphere(char **split_line, t_shape **shape_list)
void	set_sphere(char **split_line, t_config *config, int *err_flag)
{
	size_t	i;
	t_shape	*shape_node;

	shape_node = (t_shape *)malloc(sizeof(t_shape) * 1);
	shape_node->type = ST_SPHERE;
	shape_node->next = NULL;
	i = 1;
	while (split_line[i])
	{
		if (i == 1)
			shape_node->sphere.center = set_coordinates(split_line[i], err_flag);
		else if (i == 2)
			shape_node->sphere.radius = set_size(split_line[i], err_flag) / 2.0;
		else if (i == 3)
			shape_node->material.diffuse_ref = set_rgb(split_line[i], err_flag);
		else
			printf("ERROR\n");
		i++;
	}
	add_list_last(&config->shape_list, shape_node);
//	add_list_last(shape_list, shape_node);
}

//void	set_cylinder(char **split_line, t_shape **shape_list)
void	set_cylinder(char **split_line, t_config *config, int *err_flag)
{	
	size_t	i;
	t_shape	*shape_node;

	shape_node = (t_shape *)malloc(sizeof(t_shape) * 1);
	shape_node->type = ST_CYLINDER;
	shape_node->next = NULL;
	i = 1;
	while (split_line[i])
	{
		if (i == 1)
			shape_node->cylinder.pos = set_coordinates(split_line[i], err_flag);
		else if (i == 2)
			shape_node->cylinder.normal= set_orientation(split_line[i], err_flag);
		else if (i == 3)
			shape_node->cylinder.radius= set_size(split_line[i], err_flag) / 2.0;
		else if (i == 4)
			shape_node->cylinder.height = set_size(split_line[i], err_flag);
		else if (i == 5)
			shape_node->material.diffuse_ref = set_rgb(split_line[i], err_flag);
		else
			printf("ERROR\n");
		i++;
	}
	add_list_last(&config->shape_list, shape_node);
//	add_list_last(shape_list, shape_node);
}

//void	set_plane(char **split_line, t_shape **shape_list)
void	set_plane(char **split_line, t_config *config, int *err_flag)
{	
	size_t	i;
	t_shape	*shape_node;

	shape_node = (t_shape *)malloc(sizeof(t_shape) * 1);

	shape_node->type = ST_PLANE;
	shape_node->next = NULL;
	i = 1;
	while (split_line[i])
	{
		if (i == 1)
			shape_node->plane.pos = set_coordinates(split_line[i], err_flag);
		else if (i == 2)
			shape_node->plane.normal = set_orientation(split_line[i], err_flag);
		else if (i == 3)
			shape_node->material.diffuse_ref = set_rgb(split_line[i], err_flag);
		else
			printf("ERROR\n");
		i++;
	}
	add_list_last(&config->shape_list, shape_node);
//	add_list_last(shape_list, shape_node);
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
