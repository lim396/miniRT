#include "minirt.h"

void	set_ambient(char **split_line, t_config *config, int *err_flag)
{
	size_t	i;

	i = 1;
	while (split_line[i])
	{
		if (i == 1)
		{
			config->ambient.ambient_ref.r = set_ratio(split_line[i], err_flag);
			config->ambient.ambient_ref.g = set_ratio(split_line[i], err_flag);
			config->ambient.ambient_ref.b = set_ratio(split_line[i], err_flag);
		}
		else if (i == 2)
			config->ambient.ambient_illuminance = set_rgb(split_line[i], err_flag);
		else
			printf("ERROR\n");
		i++;
	}
}

void	set_light(char **split_line, t_config *config, int *err_flag)
{
	size_t	i;
	
	i = 1;
	while (split_line[i])
	{
		if (i == 1)
			config->light.vec = set_coordinates(split_line[i], err_flag);
		else if (i == 2)
			config->light.brightness_ratio = set_ratio(split_line[i], err_flag);
		else if (i == 3)
			config->light.illuminance = set_rgb(split_line[i], err_flag);
		else
			printf("ERROR\n");
		i++;
	}
}

void	set_camera(char **split_line, t_config *config, int *err_flag)
{
	size_t	i;

	i = 1;
	while (split_line[i])
	{
		if (i == 1)
			config->camera.pos = set_coordinates(split_line[i], err_flag);
		else if (i == 2)
			config->camera.orientation = set_orientation(split_line[i], err_flag);
		else if (i == 3)
			config->camera.fov = set_fov(split_line[i], err_flag);
		else
			printf("ERROR\n");
		i++;
	}
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
