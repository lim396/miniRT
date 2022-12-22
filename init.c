#include "minirt.h"

double	atod(char *str)
{
	double	minus;

	minus = 0.0;
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		minus = 1.0;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		num = (num * 10) + (*str - '0');
		str++;
	}

	


	
}

t_vec	set_vec(char *xyz)
{
	char	**split_xyz;
	t_vec	vec;

	split_xyz = split(xyz, ',');
	if (split_xyz[0])
		vec.x = atod(split_xyz[0]); //set color
	else
		printf("ERROR\n");
	if (split_xyz[1])
		vec.y = atod(split_xyz[1]);
	else
		printf("ERROR\n");
	if (split_xyz[2])
		vec.z = atod(split_xyz[2]);
	else
		printf("ERROR\n");
	return (vec);
}

t_color	set_color(char *rgb)
{
	char	**split_rgb;
	t_color	color;

	split_rgb = split(xyz, ',');
	if (split_rgb[0])
		color.r = atod(split_rgb[0]); //set color
	else
		printf("ERROR\n");
	if (split_rgb[1])
		color.g = atod(split_rgb[1]);
	else
		printf("ERROR\n");
	if (split_rgb[2])
		color.b = atod(split_rgb[2]);
	else
		printf("ERROR\n");
	return (color);
}

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
			config->ambient_illuminance = set_color(split_line[i]);
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
			config->light.vec = set_vec(split_line[i]);
		else if (i == 2)
			config->light.brightness_ratio = atod(split_line[i]);
		else if (i == 3)
			config->light.illuminance = set_color(split_line[i]);
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
			config->camera.pos = set_vec(split_line[i]);
		else if (i == 2)
			config->camera.orientation = set_vec(split_line[i]);
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
			config->shapes_list[1].shpere.center = set_vec(split_line[i]);
		else if (i == 2)
			config->shapes_list[1].sphere.radius = atod(split_line[i]) / 2.0;
		else if (i == 3)
			config->shapes_list[1].material.diffuse_ref = set_color(split_line[i]);
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
			config->shapes_list[2].plane.pos = set_vec(split_line[i]);
		else if (i == 2)
			config->shapes_list[2].plane.normal = set_vec(split_line[i]);
		else if (i == 3)
			config->shapes_list[2].material.diffuse_ref = set_color(split_line[i]); //set_color
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
			config->shapes_list[3].cylinder.pos = set_vec(split_line[i]);
		else if (i == 2)
			config->shapes_list[3].cylinder.orientation = set_vec(split_line[i]);
		else if (i == 3)
			config->shapes_list[3].cylinder.diameter = atod(split_line[i]);
		else if (i == 4)
			config->shapes_list[3].cylinder.height = atod(split_line[i]);
		else if (i == 5)
			config->shapes_list[3].material.diffuse_ref = set_color(split_line[i]);
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

t_config	init(char **argv)
{
	t_config	config;

	config = read_map(argv[1]);
	return (config);
}
