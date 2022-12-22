#include "minirt.h"

void	set_ambient(char **split_line, t_config *config)
{
	size_t	i;
	char	**split_rgb;

	i = 1;
	while (split_line[i])
	{
		if (i == 1)
			config->ambient.ambient_ref = atod(split_line[i]);
		else if (i == 2)
		{
			split_rgb = split(split_line[i]);
			config->ambient_illuminance.r = atod(split_rgb[0]); //set color
			config->ambient_illuminance.g = atod(split_rgb[1]);
			config->ambient_illuminance.b = atod(split_rgb[2]);
		}
		else
			printf("ERROR\n");
		i++;
	}
	return (config);
}

void	set_light(char **split_line, t_config *config)
{
	size_t	i;
	char	**split_xyz;
	char	**split_rgb;
	
	i = 1;
	while (split_line[i])
	{
		if (i == 1)
		{
			split_xyz = split(split_line[i]);
			config->light.vec.x = atod(split_xyz[0]); //set vec
			config->light.vec.y = atod(split_xyz[1]);
			config->light.vec.z = atod(split_xyz[2]);
		}
		else if (i == 2)
			config->light.brightness_ratio = atod(split_line[i]);
		else if (i == 3)
		{
			split_rgb = split(split_line[i]);
			config->light.illuminance.r = atod(split_rgb[0]); //set_color
			config->light.illuminance.g = atod(split_rgb[1]);
			config->light.illuminance.b = atod(split_rgb[2]);
		}
		else
			printf("ERROR\n");
		i++;
	}
	return (config);
}

void	set_camera(char **split_line, t_config *config)
{
	char	**split_xyz;

	i = 1;
	while (split_line[i])
	{
		if (i == 1)
		{
			split_xyz = split(split_line[i]);
			config->camera.pos.x = atod(split_xyz[0]); //set vec
			config->camera.pos.y = atod(split_xyz[1]);
			config->camera.pos.z = atod(split_xyz[2]);
		}
		else if (i == 2)
		{
			split_xyz = split(split_line[i]);
			config->camera.orientation.x = atod(split_xyz[0]);
			config->camera.orientation.y = atod(split_xyz[1]);
			config->camera.orientation.z = atod(split_xyz[2]);
		}
		else if (i == 3)
			config->camera.fov = atoi(split_line[i]);
		else
			printf("ERROR\n");
		i++;
	}
	return (config);
}

void	set_sphere(char **split_line, t_config *config)
{
	char	**split_xyz;
	char	**split_rgb;

						//tmp index
	config->shapes_list[1].type = ST_SPHERE;
	i = 1;
	while (split_line[i])
	{
		if (i == 1)
		{
			split_xyz = split(split_line[i]);
			config->shapes_list[1].shpere.center.x = atod(split_xyz[0]); //set vec
			config->shapes_list[1].sphere.center.y = atod(split_xyz[1]);
			config->shapes_list[1].sphere.center.z = atod(split_xyz[2]);
		}
		else if (i == 2)
			config->shapes_list[1].sphere.radius = atod(split_line[i]) / 2.0;
		else if (i == 3)
		{
			split_rgb = split(split_line[i]);
			config->shapes_list[1].material.diffuse_ref.r = atod(split_rgb[0]); //set_color
			config->shapes_list[1].material.diffuse_ref.g = atod(split_rgb[1]); //set_color
			config->shapes_list[1].material.diffuse_ref.b = atod(split_rgb[2]); //set_color
		}
		else
			printf("ERROR\n");
		i++;
	}
	return (config);
}

void	set_plane(char **split_line, t_config *config)
{	
	char	**split_xyz;
	char	**split_rgb;

						//tmp index
	config->shapes_list[2].type = ST_PLANE;
	i = 1;
	while (split_line[i])
	{
		if (i == 1)
		{
			split_xyz = split(split_line[i]);
			config->shapes_list[2].plane.pos.x = atod(split_xyz[0]); //set vec
			config->shapes_list[2].plane.pos.y = atod(split_xyz[1]);
			config->shapes_list[2].plane.pos.z = atod(split_xyz[2]);
		}
		else if (i == 2)
		{
			split_xyz = split(split_line[i]);
			config->shapes_list[2].plane.normal.x = atod(split_xyz[0]); //set vec
			config->shapes_list[2].plane.normal.y = atod(split_xyz[1]);
			config->shapes_list[2].plane.normal.z = atod(split_xyz[2]);
		}
		else if (i == 3)
		{
			split_rgb = split(split_line[i]);
			config->shapes_list[2].material.diffuse_ref.r = atod(split_rgb[0]); //set_color
			config->shapes_list[2].material.diffuse_ref.g = atod(split_rgb[1]); //set_color
			config->shapes_list[2].material.diffuse_ref.b = atod(split_rgb[2]); //set_color
		}
		else
			printf("ERROR\n");
		i++;
	}
	return (config);
}

void	set_cylinder(char **split_line, t_config *config)
{	
	char	**split_xyz;
	char	**split_rgb;

						//tmp index
	config->shapes_list[2].type = ST_CYLINDER;
	i = 1;
	while (split_line[i])
	{
		if (i == 1)
		{
			split_xyz = split(split_line[i]);
			config->shapes_list[3].cylinder.pos.x = atod(split_xyz[0]); //set vec
			config->shapes_list[3].cylinder.pos.y = atod(split_xyz[1]);
			config->shapes_list[3].cylinder.pos.z = atod(split_xyz[2]);
		}
		else if (i == 2)
		{
			split_xyz = split(split_line[i]);
			config->shapes_list[3].cylinder.orientation.x = atod(split_xyz[0]); //set vec
			config->shapes_list[3].cylinder.orientation.y = atod(split_xyz[1]);
			config->shapes_list[3].cylinder.orientation.z = atod(split_xyz[2]);
		}
		else if (i == 3)
			config->shapes_list[3].cylinder.diameter = atod(split_line[i]);
		else if (i == 4)
			config->shapes_list[3].cylinder.height = atod(split_line[i]);
		else if (i == 5)
		{
			split_rgb = split(split_line[i]);
			config->shapes_list[3].material.diffuse_ref.r = atod(split_rgb[0]); //set_color
			config->shapes_list[3].material.diffuse_ref.g = atod(split_rgb[1]); //set_color
			config->shapes_list[3].material.diffuse_ref.b = atod(split_rgb[2]); //set_color
		}
		else
			printf("ERROR\n");
		i++;
	}
	return (config);
}

bool	set_config(t_config *config, const char *line)
{
	char	**split_line;
	size_t	i;
	char	ident;
	
	config->shapes_list = malloc(sizeof(shape_t) * 4); // 4 is tmp
	i = 0;
	split_line = ft_split(line, ' ');
	if (split_line == NULL)
		return (false);
	if (split_line[0] != NULL)
	{
		if (*split_line[0] == 'A')
			set_ambient(split_line, config);
		else if (*split_line[0] == 'L')
			set_light(split_line, config);
		else if (*split_line[0] == 'C')
			set_camera(split_line, config);
		else if (*split_line[0] == 's' && *split_line[1] == 'p')
			set_sphere(split_line, config);
		else if (*split_line[0] == 'p' && *split_line[1] == 'l')
			set_plane(split_line, config);
		else if (*split_line[0] == 'c' && *split_line[1] == 'y')
			set_cylinder(split_line, config);
		else
			printf("ERROR\n");
	}
	return (true);
}

t_config	read_map(char *filename)
{
	char		*line;
	t_config	config;
	int			fd;

	fd = open(filename);
	while (true)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break;
		set_config(&config, line);
	}
	return (config);
}

void	init(char **argv)
{
	read_map(argv[1]);
}
