#include "minirt.h"

void	set_ambient(char **split_line, t_config *config)
{
	size_t	i;

	i = 1;
	while (split_line[i])
	{
		if (i == 1)
		{
			config->ambient.ambient_ref.r = atod(split_line[i]);
			config->ambient.ambient_ref.g = atod(split_line[i]);
			config->ambient.ambient_ref.b = atod(split_line[i]);
		}
		else if (i == 2)
			config->ambient.ambient_illuminance = set_color(split_line[i]);
		else
			printf("ERROR\n");
		i++;
	}
}

void	set_light(char **split_line, t_config *config)
{
	size_t	i;
	
	i = 1;
	while (split_line[i])
	{
		if (i == 1)
			config->light.vec = set_vec(split_line[i]);
		else if (i == 2)
			config->light.brightness_ratio = atod(split_line[i]);
		else if (i == 3)
			config->light.illuminance = set_color(split_line[i]);
		else
			printf("ERROR\n");
		i++;
	}
}

void	set_camera(char **split_line, t_config *config)
{
	size_t	i;

	i = 1;
	while (split_line[i])
	{
		if (i == 1)
			config->camera.pos = set_vec(split_line[i]);
		else if (i == 2)
			config->camera.orientation = set_vec(split_line[i]);
		else if (i == 3)
			config->camera.fov = atod(split_line[i]);
		else
			printf("ERROR\n");
		i++;
	}
}
